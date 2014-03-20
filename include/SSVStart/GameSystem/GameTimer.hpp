// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMETIMER
#define SSVS_GAMESYSTEM_GAMETIMER

#include "SSVStart/GameSystem/Timers/TimerBase.hpp"

namespace ssvs
{
	class GameEngine;

	class GameTimer
	{
		private:
			Uptr<TimerBase> impl, nextImpl;

		public:
			inline void refresh() noexcept
			{
				if(nextImpl == nullptr) return;

				impl.swap(nextImpl);
				nextImpl = nullptr;

				SSVU_ASSERT(nextImpl == nullptr);
			}

			inline TimerBase* operator->()				{ return impl.get(); }
			inline const TimerBase* operator->() const	{ return impl.get(); }

			template<typename T> inline T& getImpl() { return reinterpret_cast<T&>(*impl); }
			template<typename T, typename... TArgs> inline void setImpl(GameEngine& mGameEngine, TArgs&&... mArgs)
			{
				SSVU_ASSERT(nextImpl == nullptr);
				nextImpl = std::make_unique<T>(mGameEngine, std::forward<TArgs>(mArgs)...);
			}
	};
}

#endif
