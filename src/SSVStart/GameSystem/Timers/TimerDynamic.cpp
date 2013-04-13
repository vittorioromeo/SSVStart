#include "SSVStart/GameSystem/Timers/TimerDynamic.h"
#include "SSVStart/GameSystem/GameWindow.h"

namespace ssvs
{
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

	DynamicTimer& createDynamicTimer(GameWindow& mGameWindow) { return *(new DynamicTimer{mGameWindow}); }
}
