#include "SSVStart/GameSystem/Timers.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
	TimerBase::TimerBase(GameWindow& mGameWindow) : gameWindow(mGameWindow) { }
	TimerBase::~TimerBase() { }

	void TimerBase::runUpdate()		{ }
	void TimerBase::runDraw()		{ gameWindow.runDraw(); }
	void TimerBase::runFrameTime()	{ frameTime = clock.restart().asSeconds() * 60.f; }
	void TimerBase::runFps()		{ fps = 60.f / frameTime; }

	float TimerBase::getFrameTime() const 	{ return frameTime; }
	float TimerBase::getFps() const 		{ return fps; }



	StaticTimer::StaticTimer(GameWindow& mGameWindow, float mStep, float mSpeedMultiplier) : TimerBase(mGameWindow), step{mStep}, speedMultiplier{mSpeedMultiplier} { }
	StaticTimer::~StaticTimer() { }

	void StaticTimer::runUpdate()
	{
		loops = 0;
		accumulatedTime += frameTime;
		while(accumulatedTime >= step * speedMultiplier && loops < maxLoops)
		{
			gameWindow.runInput();
			gameWindow.runUpdate(step);
			accumulatedTime -= step * speedMultiplier;
			++loops;
		}
	}



	DynamicTimer::DynamicTimer(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }
	DynamicTimer::~DynamicTimer() { }

	void DynamicTimer::runUpdate()
	{
		gameWindow.runInput();
		gameWindow.runUpdate(frameTime);
	}
	void DynamicTimer::runFps()
	{
		if(frameTime > frameTimeLimit) frameTime = frameTimeLimit;
		TimerBase::runFps();
	}



	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep, float mSpeedMultiplier) { return *(new StaticTimer{mGameWindow, mStep, mSpeedMultiplier}); }
	DynamicTimer& createDynamicTimer(GameWindow& mGameWindow) { return *(new DynamicTimer{mGameWindow}); }
}
