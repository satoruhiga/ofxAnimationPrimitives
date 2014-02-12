#pragma once

#include "ofMain.h"

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class Composition
{
	template <typename T>
	using RefType = ofPtr<T>;
	
public:
	
	typedef RefType<Composition> Ref;
	
	// factory method
	template <typename T>
	static Composition::Ref New(float fadein_duration = 0, float scene_total_duration = std::numeric_limits<float>::infinity(), float fadeout_duration = 0);
	
public:
	
	virtual void setup() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual void viewWillAppear() {}
	virtual void viewDidAppear() {}
	virtual void viewWillDisappear() {}
	virtual void viewDidDisappear() {}

public:
	
	// property
	int getElapsedFrame() const;
	float getElapsedTime() const;
	
	float getDuration() const;
	float getPosition() const;
	
	float getAlpha() const;
	
public:
	
	void play();
	void play(float fadein_duration, float scene_total_duration = std::numeric_limits<float>::infinity(), float fadeout_duration = 0);
	void stop(float fadeout_duration = 0);
	
	bool isPlaying() const;
	bool isFinished() const;
	
	void reset();
	
public:
	
	// events
	
	enum Cue {
		WILL_APPEAR,
		DID_APPEAR,
		WILL_DISAPPEAR,
		DID_DISAPPEAR
	};
	
	Composition& after(Cue event, const Composition::Ref&);
	Composition& at(float time, const Composition::Ref&);
	
protected:
	
	Composition();
	virtual ~Composition();

private:
	
	float alpha;
	int elapsed_frame;
	float elapsed_time;
	
	float duration;
	float fadein_duration, fadeout_duration;
	float fadeout_time;
	
	multimap<Cue, Composition::Ref> cue_event_map;
	multimap<float, Composition::Ref> time_event_map;
	
	void procTimeEvent(float t0, float t1);
	void procCueEvent(Cue cue);
	
	enum CompositionState {
		STARTED,
		PAUSED,
		FADEIN,
		PLAYING,
		FADEOUT,
		FINISHED
	} state;

	friend class CompositionRunner;
	
	void prepare(float fadein_duration, float scene_total_duration, float fadeout_duration);
	void updateState();
	void updateAlphaValue();
	
	void _update(float tick);
	void _draw();
	
	void _viewWillAppear();
	void _viewDidAppear();
	void _viewWillDisappear();
	void _viewDidDisappear();
	
	// noncopyable
	Composition(const Composition&) {}
	Composition& operator=(const Composition&) {}
};


class CompositionRunner
{
public:
	
	static CompositionRunner& defaultRunner()
	{
		static CompositionRunner o;
		return o;
	}
	
	void update(float tick = ofGetLastFrameTime())
	{
		for (int i = 0; i < comps.size(); i++)
		{
			comps[i]->_update(tick);
		}
	}
	
	void draw()
	{
		for (int i = 0; i < comps.size(); i++)
		{
			comps[i]->_draw();
		}
	}
	
public: // internal use
	
	void registerComposition(Composition* o)
	{
		if (find(comps.begin(), comps.end(), o) != comps.end()) return;
		comps.push_back(o);
	}

	void unregisterComposition(Composition* o)
	{
		if (find(comps.begin(), comps.end(), o) == comps.end()) return;
		comps.erase(remove(comps.begin(), comps.end(), o), comps.end());
	}

	void clear()
	{
		comps.clear();
	}
	
private:
	
	vector<Composition*> comps;
	
	// noncopyable
	CompositionRunner() {}
	~CompositionRunner() {}
	CompositionRunner(const CompositionRunner&) {}
	CompositionRunner& operator=(const CompositionRunner&) {}
};

#include "detail/Composition.inc.h"

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE