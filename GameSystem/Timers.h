#ifndef SSVS_TRAITS_WINDOWTIMERTRAITS
#define SSVS_TRAITS_WINDOWTIMERTRAITS

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameSystem/GameState.h"
#include "GameSystem/GameWindow.h"

namespace ssvs
{
	struct TimerBase
	{
		GameWindow& gameWindow;
		sf::Clock clock;
		float frameTime{0}, fps{0};

		TimerBase(GameWindow& mGameWindow) : gameWindow(mGameWindow) { }

		virtual void runUpdate() 	{ }
		virtual void runDraw() 		{ gameWindow.gamePtr->draw(); }
		virtual void runFrameTime() { frameTime = clock.restart().asSeconds() * 60.f; }
		virtual void runFps()		{ fps = 60.f / frameTime; }

		float getFrameTime() const 	{ return frameTime; }
		float getFps() const 		{ return fps; }
	};

	
	struct StaticTimer : public TimerBase
	{
		float step{1.f};
		float accumulatedTime{0}, loops{0}, maxLoops{10};

		StaticTimer(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }

		void runUpdate() override
		{
			loops = 0;
			accumulatedTime += frameTime;
			while(accumulatedTime >= step && loops < maxLoops) { gameWindow.gamePtr->update(step); accumulatedTime -= step; ++loops; }
		}
	};

	struct DynamicTimer : public TimerBase
	{
		float frameTimeLimit{4.f};

		DynamicTimer(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }

		void runUpdate() override { gameWindow.gamePtr->update(frameTime); }
		void runFps() override
		{			
			if(frameTime > frameTimeLimit) frameTime = frameTimeLimit;
			TimerBase::runFps();
		}
	};
}

#endif
