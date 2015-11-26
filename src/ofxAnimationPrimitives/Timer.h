#pragma once

#include "ofMain.h"

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

void initTimer();

struct Ticker
{
	virtual ~Ticker() { stop(); }
	virtual void tick(float delta) {}
	
	void play();
	void stop();
};

class Timer : protected Ticker
{
public:
	
	enum {
		FOREVER = -1
	};
	
	ofEvent<int> timerEvent;
	
	Timer() : remain(0), duration(0), repeat(0) {}
	
	void start(float duration, int repeat = FOREVER)
	{
		this->duration = duration;
		this->remain = duration;
		this->repeat = repeat;
		
		count = 0;
		
		Ticker::play();
	}
	
	void stop()
	{
		Ticker::stop();
	}
	
	int getCount() const { return count; }
	
protected:
	
	float remain, duration;
	int repeat, count;
	
	void tick(float delta)
	{
		remain -= delta;
		
		if (remain > 0) return;
		
		int N = count;
		ofNotifyEvent(timerEvent, N, this);
		
		count++;
		
		if (repeat < 0
			|| count < repeat)
		{
			remain += duration;
		}
		else
		{
			stop();
		}
	}
};

#pragma mark -

class Clock
{
public:
	
	virtual float getTime() const { return ofGetLastFrameTime(); }
	
	void update()
	{
		float dt = getTime();
		for (int i = 0; i < time_related().size(); i++)
			time_related()[i]->tick(dt);
	}
	
	void makeSystemClock() { system_clock = this; }
	
public:
	
	static Clock* getClock() { return system_clock; }
	
	static void regist(Ticker *o)
	{
		if (find(time_related().begin(), time_related().end(), o) != time_related().end()) return;
		time_related().push_back(o);
	}
	
	static void unregist(Ticker *o)
	{
		vector<Ticker*>::iterator it = remove(time_related().begin(), time_related().end(), o);
		time_related().erase(it, time_related().end());
	}
	
protected:
	
	static Clock *system_clock;
	static vector<Ticker*>& time_related()
	{
		static vector<Ticker*> *p = new vector<Ticker*>;
		return *p;
	}
};

class Tempo : public Clock
{
public:
	
	Tempo() : bpm(120) {}
	
	void setBpm(float v) { bpm = v; }
	float getBpm() const { return bpm; }
	
	float getTime() const
	{
		return ofGetLastFrameTime() * (bpm / 60);
	}
	
protected:
	
	float bpm;
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
