#include "SSVStart/GameSystem/Timers/TimerStatic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	StaticTimer::StaticTimer(GameWindow& mGameWindow, float mStep, float mSpeed, float mMaxLoops) : TimerBase(mGameWindow), step{mStep}, speed{mSpeed}, maxLoops{mMaxLoops} { }
	StaticTimer::~StaticTimer() { }

	void StaticTimer::runUpdate()
	{
		loops = 0;
		accumulatedTime += frameTime;
		while(accumulatedTime >= speed && loops < maxLoops)
		{
			gameWindow.runInput();
			gameWindow.runUpdate(step);
			accumulatedTime -= speed;
			++loops;
		}
	}

	float StaticTimer::getStep() const				{ return step; }
	float StaticTimer::getSpeed() const				{ return speed; }
	float StaticTimer::getMaxLoops() const			{ return maxLoops; }
	float StaticTimer::getAccumulatedTime() const	{ return accumulatedTime; }
	float StaticTimer::getLoops() const				{ return loops; }

	void StaticTimer::setStep(float mStep)			{ step = mStep; }
	void StaticTimer::setSpeed(float mSpeed)		{ speed = mSpeed; }
	void StaticTimer::setMaxLoops(float mMaxLoops)	{ maxLoops = mMaxLoops; }

	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep, float mSpeed, float mMaxLoops) { return *(new StaticTimer{mGameWindow, mStep, mSpeed, mMaxLoops}); }
}
