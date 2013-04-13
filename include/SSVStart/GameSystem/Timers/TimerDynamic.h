#ifndef SSVS_GAMESYSTEM_TIMERS_DYNAMIC
#define SSVS_GAMESYSTEM_TIMERS_DYNAMIC

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/GameSystem/Timers/TimerBase.h"

namespace ssvs
{
	class GameWindow;

	struct DynamicTimer : public TimerBase
	{
		float frameTimeLimit{4.f};

		DynamicTimer(GameWindow& mGameWindow);
		~DynamicTimer();

		void runUpdate() override;
		void runFps() override;
	};

	DynamicTimer& createDynamicTimer(GameWindow& mGameWindow);
}

#endif
