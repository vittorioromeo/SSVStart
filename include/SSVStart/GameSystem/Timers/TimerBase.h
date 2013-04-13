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

		float getFrameTime() const;
		float getFps() const;
	};
}

#endif
