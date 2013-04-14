#include "SSVStart/GameSystem/Timers/TimerStatic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	StaticTimer::StaticTimer(GameWindow& mGameWindow, float mStep, float mTimeSlice, float mMaxLoops) : TimerBase(mGameWindow), step{mStep}, timeSlice{mTimeSlice}, maxLoops{mMaxLoops} { }
	StaticTimer::~StaticTimer() { }

	void StaticTimer::runUpdate()
	{
		loops = 0;
		time += frameTime;
		while(time >= timeSlice && loops < maxLoops)
		{
			gameWindow.runUpdate(step);
			time -= timeSlice;
			++loops;
		}
	}

	float StaticTimer::getStep() const				{ return step; }
	float StaticTimer::getTimeSlice() const			{ return timeSlice; }
	float StaticTimer::getMaxLoops() const			{ return maxLoops; }
	float StaticTimer::getTime() const				{ return time; }
	float StaticTimer::getLoops() const				{ return loops; }

	void StaticTimer::setStep(float mStep)				{ step = mStep; }
	void StaticTimer::setTimeSlice(float mTimeSlice)	{ timeSlice = mTimeSlice; }
	void StaticTimer::setMaxLoops(float mMaxLoops)		{ maxLoops = mMaxLoops; }

	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep, float mSpeed, float mMaxLoops) { return *(new StaticTimer{mGameWindow, mStep, mSpeed, mMaxLoops}); }
}
