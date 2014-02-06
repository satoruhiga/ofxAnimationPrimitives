#pragma once

#include "ofMain.h"

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

struct Timer
{
	virtual ~Timer() { stop(); }
	virtual void tick(float time_diff) {}
	
	void play();
	void stop();
};

class Clock
{
public:
	
	virtual float get() const { return ofGetLastFrameTime(); }
	
	void update()
	{
		float dt = get();
		for (int i = 0; i < time_related().size(); i++)
			time_related()[i]->tick(dt);
	}
	
	void makeSystemClock() { system_clock = this; }
	
public:
	
	static Clock* getClock() { return system_clock; }
	
	static void regist(Timer *o)
	{
		if (find(time_related().begin(), time_related().end(), o) != time_related().end()) return;
		time_related().push_back(o);
	}
	
	static void unregist(Timer *o)
	{
		vector<Timer*>::iterator it = remove(time_related().begin(), time_related().end(), o);
		time_related().erase(it, time_related().end());
	}
	
protected:
	
	static Clock *system_clock;
	static vector<Timer*>& time_related()
	{
		static vector<Timer*> *p = new vector<Timer*>;
		return *p;
	}
};

class Tempo : public Clock
{
public:
	
	Tempo() : bpm(120) {}
	
	void setBpm(float v) { bpm = v; }
	float getBpm() const { return bpm; }
	
	float get() const
	{
		return ofGetLastFrameTime() * (bpm / 60);
	}
	
protected:
	
	float bpm;
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
