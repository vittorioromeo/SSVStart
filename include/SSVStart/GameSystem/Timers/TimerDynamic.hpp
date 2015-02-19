// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_TIMERS_DYNAMIC
#define SSVS_GAMESYSTEM_TIMERS_DYNAMIC

namespace ssvs
{
	class TimerDynamic final : public TimerBase
	{
		private:
			FT frameTimeLimit{4.f};

		public:
			inline TimerDynamic(GameEngine& mGameEngine) noexcept : TimerBase(mGameEngine) { }

			inline void runUpdate() override
			{
				gameEngine.updateFromTimer(frameTime);
			}
			inline void runFPS() override
			{
				ssvu::clampMax(frameTime, frameTimeLimit);
				TimerBase::runFPS();
			}
	};
}

#endif
