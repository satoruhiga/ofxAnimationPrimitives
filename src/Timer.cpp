#include "Timer.h"

BEGIN_OFX_ANIMATION_PRIMITIVES_NAMESPACE

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

END_OFX_ANIMATION_PRIMITIVES_NAMESPACE