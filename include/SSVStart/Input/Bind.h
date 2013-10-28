// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

#include <vector>
#include <functional>
#include "SSVStart/Input/Trigger.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Manager;

		class Bind
		{
			private:
				Trigger trigger;
				InputFunc on, off;

				inline std::size_t getPriority() const { std::size_t max{0}; for(auto& c : trigger.getCombos()) max = std::max(c.getKeys().count() + c.getBtns().count(), max); return max; }

			public:
				Bind(Trigger mTrigger, const InputFunc& mOn = nullptr, const InputFunc& mOff = nullptr) : trigger{std::move(mTrigger)}, on{mOn}, off{mOff} { }

				inline void update(Manager& mManager, float mFT, GameWindow& mGameWindow)	{ trigger.isActive(mManager, mGameWindow) ? callOn(mFT) : callOff(mFT); }
				inline void refresh(Manager& mManager, GameWindow& mGameWindow)				{ trigger.refresh(mManager, mGameWindow); }

				inline void callOn(float mFT) const		{ if(on != nullptr) on(mFT); }
				inline void callOff(float mFT) const	{ if(off != nullptr) off(mFT); }

				inline bool operator<(const Bind& mRhs) const noexcept { return getPriority() > mRhs.getPriority(); }\
		};
	}
}

#endif
