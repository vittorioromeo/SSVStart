// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_DYNAMIC
#define SSVS_GAMESYSTEM_TIMERS_DYNAMIC

#include "SSVStart/GameSystem/Timers/TimerBase.hpp"
#include "SSVStart/GameSystem/GameWindow.hpp"

namespace ssvs
{
	class TimerDynamic final : public TimerBase
	{
		private:
			FT frameTimeLimit{4.f};

		public:
			TimerDynamic(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }

			inline void runUpdate() override { gameWindow.runUpdate(frameTime); }
			inline void runFps() override
			{
				ssvu::clampMax(frameTime, frameTimeLimit);
				TimerBase::runFps();
			}
	};
}

#endif
