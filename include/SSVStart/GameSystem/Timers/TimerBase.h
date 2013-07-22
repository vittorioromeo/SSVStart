// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_BASE
#define SSVS_GAMESYSTEM_TIMERS_BASE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class GameWindow;

	struct TimerBase
	{
		GameWindow& gameWindow;
		sf::Clock clock;
		float frameTime{0}, fps{0};

		TimerBase(GameWindow& mGameWindow);
		virtual ~TimerBase();

		virtual void runUpdate();
		virtual void runDraw();
		virtual void runFrameTime();
		virtual void runFps();

		inline float getFrameTime() const	{ return frameTime; }
		inline float getFps() const			{ return fps; }
	};
}

#endif
