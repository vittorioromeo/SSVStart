// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

#include <vector>
#include <functional>
#include "SSVStart/Input/Trigger.hpp"
#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	namespace Input
	{
		class InputState;
		class Manager;

		class Bind
		{
			private:
				Trigger trigger;
				InputFunc on, off;

				inline std::size_t getPriority() const { std::size_t max{0}; for(auto& c : trigger.getCombos()) max = std::max(c.getKeys().count() + c.getBtns().count(), max); return max; }

			public:
				Bind(Trigger mTrigger, const InputFunc& mOn = nullptr, const InputFunc& mOff = nullptr) : trigger{std::move(mTrigger)}, on{mOn}, off{mOff} { }

				inline void update(Manager& mManager, FT mFT, InputState& mInputState)	{ trigger.isActive(mManager, mInputState) ? callOn(mFT) : callOff(mFT); }
				inline void refresh(Manager& mManager, InputState& mInputState)			{ trigger.refresh(mManager, mInputState); }

				inline void callOn(FT mFT) const	{ if(on != nullptr) on(mFT); }
				inline void callOff(FT mFT) const	{ if(off != nullptr) off(mFT); }

				inline bool operator<(const Bind& mRhs) const noexcept { return getPriority() > mRhs.getPriority(); }\
		};
	}
}

#endif
