
Composition::Duration::Duration(float fadein_duration, float total_duration, float fadeout_duration)
	:fadein_duration(fadein_duration)
	,total_duration(total_duration)
	,fadeout_duration(fadeout_duration)
{
}


#pragma mark - Composition

Composition::Composition() :
	state(PAUSED),
	alpha(0),
	alpha_delta(0),
	elapsed_time(0),
	duration(0, 0, 0)
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
Composition::Ref Composition::New()
{
	return Composition::Ref(new T);
}

/*
http://nedbatchelder.com/code/cog/
$ cog.py -r SomoSourceCode.h

[[[cog
import cog

tmpl = '''template <typename T, %(A)s>
Composition::Ref Composition::New(%(B)s)
{
	return Composition::Ref(new T(%(C)s));
}
'''

cog.outl('')
for i in xrange(1, 18):
	a = ', '.join(['typename A%i' % x for x in range(i)])
	b = ', '.join(['const A%i& a%i' % (x, x) for x in range(i)])
	c = ', '.join(['a%i' % x for x in range(i)])
	cog.outl(tmpl % {'A':a, 'B':b, 'C':c})

]]]*/

template <typename T, typename A0>
Composition::Ref Composition::New(const A0& a0)
{
	return Composition::Ref(new T(a0));
}

template <typename T, typename A0, typename A1>
Composition::Ref Composition::New(const A0& a0, const A1& a1)
{
	return Composition::Ref(new T(a0, a1));
}

template <typename T, typename A0, typename A1, typename A2>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2)
{
	return Composition::Ref(new T(a0, a1, a2));
}

template <typename T, typename A0, typename A1, typename A2, typename A3>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
{
	return Composition::Ref(new T(a0, a1, a2, a3));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
}

//[[[end]]]

inline float Composition::getElapsedTime() const { return elapsed_time; }
inline float Composition::getDuration() const { return duration.total_duration; }
inline float Composition::getPosition() const { return elapsed_time / (duration.total_duration + std::numeric_limits<float>::denorm_min()); }
inline float Composition::getAlpha() const { return alpha; }
inline bool Composition::isPlaying() const { return state != PAUSED && state != FINISHED; }
inline bool Composition::isFinished() const { return state == FINISHED; }

void Composition::reset()
{
	CompositionRunner::defaultRunner().unregisterComposition(this);
	
	state = PAUSED;
	elapsed_time = 0;
	alpha = 0;
	alpha_delta = 0;
	
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

	if (duration.fadein_duration <= 0)
		alpha_delta = 1.;
	else
		alpha_delta = 1. / duration.fadein_duration;
	
	state = STARTED;
	
	CompositionRunner::defaultRunner().registerComposition(this);
}

void Composition::play(float fadein_duration, float scene_total_duration, float fadeout_duration)
{
	duration = Duration(fadein_duration, scene_total_duration, fadeout_duration);
	Composition::play();
}

void Composition::stop(float fadeout_duration)
{
	if (state == FADEOUT)
	{
		ofLogWarning("Composition") << "stop method called multiple times.";
		return;
	}

	if (fadeout_duration <= 0)
		alpha_delta = -alpha;
	else
		alpha_delta = -alpha / fadeout_duration;
}

void Composition::_update(float tick)
{
	if (!isPlaying()) return;
	
	float last_elapsed_time = elapsed_time;
	elapsed_time += tick;
	alpha += alpha_delta * tick;
	
	updateState();
	
	procTimeEvent(last_elapsed_time, elapsed_time);
		
	if (isPlaying())
		update();
}

void Composition::_draw()
{
	if (!isPlaying()) return;
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	ofPushStyle();
	ofPushView();
	draw();
	ofPopView();
	ofPopStyle();
	glPopAttrib();
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
	if (state == STARTED && alpha_delta > 0.)
	{
		state = FADEIN;
		
		_viewWillAppear();
	}
	if (state == FADEIN && alpha >= 1.)
	{
		alpha = 1;
		alpha_delta = 0;
		state = PLAYING;
		
		_viewDidAppear();
	}
	if (state == PLAYING && alpha_delta < 0.)
	{
		state = FADEOUT;
		
		_viewWillDisappear();
	}
	if (state == FADEOUT && alpha <= 0.)
	{
		alpha = 0;
		alpha_delta = 0;
		state = FINISHED;
		
		_viewDidDisappear();
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

Composition::Ref Composition::after(Cue event, Composition::Ref o, Duration s)
{
	if (o.get() == this)
	{
		throw;
	}
	
	cue_event_map.insert(make_pair(event, o));
	duration = s;
	
	return o;
}

Composition::Ref Composition::at(float time, Composition::Ref o, Duration s)
{
	if (o.get() == this)
	{
		throw;
	}
	
	time_event_map.insert(make_pair(time, o));
	duration = s;
	
	return o;
}

#pragma mark - CompositionRunner

