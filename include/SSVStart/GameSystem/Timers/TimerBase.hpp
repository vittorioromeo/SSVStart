// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_BASE
#define SSVS_GAMESYSTEM_TIMERS_BASE

namespace ssvs
{
	class GameEngine;

	class TimerBase
	{
		protected:
			GameEngine& gameEngine;
			sf::Clock clock;
			FT frameTime{0};
			float fps{0};

		public:
			inline TimerBase(GameEngine& mGameEngine) noexcept : gameEngine(mGameEngine) { }
			inline virtual ~TimerBase() { }

			inline virtual void runUpdate()		{ }
			inline virtual void runFrameTime()	{ frameTime = ssvu::getSecondsToFT(clock.restart().asSeconds()); }
			inline virtual void runFPS()		{ fps = ssvu::getFTToFPS(frameTime); }
			virtual void runDraw();

			inline FT getFrameTime() const noexcept	{ return frameTime; }
			inline float getFPS() const noexcept	{ return fps; }
	};
}

#endif
