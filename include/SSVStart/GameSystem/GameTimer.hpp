// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMETIMER
#define SSVS_GAMESYSTEM_GAMETIMER

namespace ssvs
{
	class GameEngine;

	class GameTimer
	{
		private:
			UPtr<TimerBase> impl, nextImpl;

		public:
			inline void refresh() noexcept
			{
				if(nextImpl == nullptr) return;

				impl.swap(nextImpl);
				nextImpl = nullptr;

				SSVU_ASSERT(nextImpl == nullptr);
			}

			inline auto operator->()		{ return impl.get(); }
			inline auto operator->() const	{ return impl.get(); }

			template<typename T> inline T& getImpl() noexcept
			{
				SSVU_ASSERT(impl != nullptr);
				return ssvu::castUp<T>(*impl);
			}
			template<typename T, typename... TArgs> inline void setImpl(GameEngine& mGameEngine, TArgs&&... mArgs)
			{
				nextImpl = ssvu::makeUPtr<T>(mGameEngine, FWD(mArgs)...);
			}
	};
}

#endif
