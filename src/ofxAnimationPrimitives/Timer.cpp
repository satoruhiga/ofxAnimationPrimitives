#include "Timer.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

Clock* Clock::system_clock = NULL;

struct Ticker
{
	Clock clock;
	
	Ticker()
	{
		clock.makeSystemClock();
		ofAddListener(ofEvents().update, this, &Ticker::onUpdate);
	}
	
	void onUpdate(ofEventArgs &e)
	{
		Clock::getClock()->update();
	}
};

static Ticker ticker;

// Timer

void Timer::play()
{
	Clock::regist(this);
}

void Timer::stop()
{
	Clock::unregist(this);
}

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE