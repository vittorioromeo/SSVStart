// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_DYNAMIC
#define SSVS_GAMESYSTEM_TIMERS_DYNAMIC

#include "SSVStart/GameSystem/Timers/TimerBase.h"

namespace ssvs
{
	class GameWindow;

	class DynamicTimer : public TimerBase
	{
		private:
			float frameTimeLimit{4.f};

		public:
			DynamicTimer(GameWindow& mGameWindow) : TimerBase(mGameWindow) { }

			void runUpdate() override;
			inline void runFps() override
			{
				if(frameTime > frameTimeLimit) frameTime = frameTimeLimit;
				TimerBase::runFps();
			}
	};
}

#endif
