#pragma once

#include "ofMain.h"

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class Composition
{
public:
	
	typedef ofPtr<Composition> Ref;
	
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
	void play(float scene_total_duration);
	void play(float fadein_duration, float scene_total_duration, float fadeout_duration);
	void stop(float fadeout_duration = 0);
	
	bool isPlaying() const;
	bool isFinished() const;
	
	void reset();
	
public:
	
	// events
	
	enum Trigger {
		WILL_APPEAR,
		DID_APPEAR,
		WILL_DISAPPEAR,
		DID_DISAPPEAR
	};
	
	ofEvent<Trigger> onTrigger;
	
	struct Duration {
		float fadein_duration;
		float total_duration;
		float fadeout_duration;
		
		Duration(float total_duration = std::numeric_limits<float>::infinity());
		Duration(float fadein_duration, float total_duration, float fadeout_duration);
	};
	
	Composition::Ref on(Trigger event, Composition::Ref, Duration s = Duration());
	Composition::Ref at(float time, Composition::Ref, Duration s = Duration());
	
public:

	// factory method

	template <typename T>
	static Composition::Ref New();
	
	/*
	http://nedbatchelder.com/code/cog/
	$ cog.py -r SomoSourceCode.h

	[[[cog
	import cog
	
	tmpl = '''template <typename T, %(A)s>
	static Composition::Ref New(%(B)s);
	'''
	
	cog.outl('')
	for i in xrange(1, 18):
		a = ', '.join(['typename A%i' % x for x in range(i)])
		b = ', '.join(['const A%i& a%i' % (x, x) for x in range(i)])
		c = ', '.join(['a%i' % x for x in range(i)])
		cog.outl(tmpl % {'A':a, 'B':b, 'C':c})
	
	]]]*/

	template <typename T, typename A0>
	static Composition::Ref New(const A0& a0);

	template <typename T, typename A0, typename A1>
	static Composition::Ref New(const A0& a0, const A1& a1);

	template <typename T, typename A0, typename A1, typename A2>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2);

	template <typename T, typename A0, typename A1, typename A2, typename A3>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
	static Composition::Ref New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16);

	//[[[end]]]
		
protected:
	
	Composition();
	virtual ~Composition();

private:
	
	float alpha, alpha_delta;
	float elapsed_time;
	
	Duration duration;
	
	multimap<Trigger, Composition::Ref> trigger_event_map;
	multimap<float, Composition::Ref> time_event_map;
	
	void procTimeEvent(float t0, float t1);
	void procTriggerEvent(Trigger trigger);
	
	enum CompositionState {
		PAUSED,
		STARTED,
		FADEIN,
		PLAYING,
		FADEOUT,
		FINISHED
	} state;

	friend class CompositionRunner;
	
	void updateState();
	
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