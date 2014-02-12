#pragma mark - Composition

Composition::Composition() :
	state(PAUSED),
	alpha(0),
	elapsed_time(0),
	duration(0),
	fadein_duration(0),
	fadeout_duration(0),
	fadeout_time(0)
{
}

Composition::~Composition()
{
	if (isPlaying())
	{
		_viewWillAppear();
		_viewDidAppear();
	}
}

template <typename T>
Composition::Ref Composition::New(float fadein_duration, float scene_total_duration, float fadeout_duration)
{
	Composition::Ref o = Composition::Ref(new T);
	o->prepare(fadein_duration, scene_total_duration, fadeout_duration);
	return o;
}

inline float Composition::getElapsedTime() const { return elapsed_time; }
inline float Composition::getDuration() const { return duration; }
inline float Composition::getPosition() const { return elapsed_time / (duration + std::numeric_limits<float>::denorm_min()); }
inline float Composition::getAlpha() const { return alpha; }
inline bool Composition::isPlaying() const { return state != PAUSED && state != FINISHED; }
inline bool Composition::isFinished() const { return state == FINISHED; }

void Composition::prepare(float fadein_duration, float scene_total_duration, float fadeout_duration)
{
	this->fadein_duration = fadein_duration;
	this->fadeout_duration = fadeout_duration;
	this->duration = scene_total_duration;
	
	this->fadeout_time = this->duration - this->fadeout_duration;
}

void Composition::reset()
{
	state = PAUSED;
	elapsed_time = 0;
	alpha = 0;
	
	{
		multimap<Cue, Composition::Ref>::iterator it = cue_event_map.begin();
		while (it != cue_event_map.end())
		{
			Composition::Ref &o = it->second;
			o->reset();
			it++;
		}
	}
	
	{
		multimap<float, Composition::Ref>::iterator it = time_event_map.begin();
		while (it != time_event_map.end())
		{
			Composition::Ref &o = it->second;
			o->reset();
			it++;
		}
	}
}

void Composition::play()
{
	if (isPlaying())
	{
		ofLogWarning("Composition") << "play method called multiple times.";
		return;
	}

	CompositionRunner::defaultRunner().registerComposition(this);
	
	state = STARTED;
}

void Composition::play(float fadein_duration, float scene_total_duration, float fadeout_duration)
{
	prepare(fadein_duration, scene_total_duration, fadeout_duration);
	Composition::play();
}

void Composition::stop(float fadeout_duration)
{
	if (state == FADEOUT)
	{
		ofLogWarning("Composition") << "stop method called multiple times.";
		return;
	}

	prepare(0, elapsed_time + fadeout_duration, fadeout_duration);
}

void Composition::_update(float tick)
{
	if (!isPlaying()) return;
	
	float last_elapsed_time = elapsed_time;
	elapsed_time += tick;
	
	updateState();
	updateAlphaValue();
	
	procTimeEvent(last_elapsed_time, elapsed_time);
		
	if (isPlaying())
		update();
}

void Composition::_draw()
{
	if (!isPlaying()) return;
	
	draw();
}

void Composition::_viewWillAppear()
{
	viewWillAppear();
	
	procCueEvent(WILL_APPEAR);
}

void Composition::_viewDidAppear()
{
	viewDidAppear();
	
	procCueEvent(DID_APPEAR);
}

void Composition::_viewWillDisappear()
{
	viewWillDisappear();
	
	procCueEvent(WILL_DISAPPEAR);
}

void Composition::_viewDidDisappear()
{
	viewDidDisappear();
	
	procCueEvent(DID_DISAPPEAR);
	CompositionRunner::defaultRunner().unregisterComposition(this);
}

void Composition::updateState()
{
	CompositionState s = state;
	
	if (state == STARTED)
	{
		_viewWillAppear();
		s = FADEIN;
	}
	if (state == FADEIN && elapsed_time > fadein_duration)
	{
		_viewDidAppear();
		s = PLAYING;
	}
	if (state == PLAYING && elapsed_time > fadeout_time)
	{
		_viewWillDisappear();
		s = FADEOUT;
	}
	if (state == FADEOUT && elapsed_time > duration)
	{
		_viewDidDisappear();
		s = FINISHED;
	}
	
	state = s;
}

void Composition::updateAlphaValue()
{
	if (state == PLAYING)
	{
		alpha = 1;
	}
	else if (state == FADEIN)
	{
		if (fadein_duration == 0)
		{
			alpha = 1;
		}
		else
		{
			alpha = ofMap(elapsed_time, 0, fadein_duration, 0, 1, true);
		}
	}
	else if (state == FADEOUT)
	{
		if (fadeout_duration == 0)
		{
			alpha = 0;
		}
		else
		{
			alpha = ofMap(elapsed_time, fadeout_time, duration, 1, 0, true);
		}
	}
	else
	{
		alpha = 0;
	}
}

void Composition::procTimeEvent(float t0, float t1)
{
	multimap<float, Composition::Ref>::iterator begin = time_event_map.lower_bound(t0);
	multimap<float, Composition::Ref>::iterator end = time_event_map.upper_bound(t1);
	
	if (begin == end) return;
	
	multimap<float, Composition::Ref>::iterator it = begin;
	
	while (it != end)
	{
		Composition::Ref &o = it->second;
		o->play();
		it++;
	}
}

void Composition::procCueEvent(Cue cue)
{
	if (cue_event_map.count(cue))
	{
		std::pair<multimap<Cue, Composition::Ref>::iterator,
		multimap<Cue, Composition::Ref>::iterator> range = cue_event_map.equal_range(cue);
		multimap<Cue, Composition::Ref>::iterator it = range.first;
		while (it != range.second)
		{
			Composition::Ref &o = it->second;
			o->play();
			it++;
		}
	}
}

Composition& Composition::after(Cue event, const Composition::Ref& o)
{
	if (o.get() == this)
	{
		throw;
	}
	cue_event_map.insert(make_pair(event, o));
	
	return *this;
}

Composition& Composition::at(float time, const Composition::Ref& o)
{
	if (o.get() == this)
	{
		throw;
	}
	time_event_map.insert(make_pair(time, o));
	return *this;
}

#pragma mark - CompositionRunner

