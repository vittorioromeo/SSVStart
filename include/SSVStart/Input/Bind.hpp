// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

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
				std::size_t priority{0u};
				Type type{Type::Always};
				Mode mode{Mode::Overlap};
				bool released{true};

				inline bool isDown(Manager& mManager, InputState& mInputState) const
				{
					for(const auto& c : trigger.getCombos()) if(c.isDown(mManager, mInputState, mode)) return true;
					return false;
				}

				inline void recalculatePriority()
				{
					std::size_t max{0u};
					for(auto& c : trigger.getCombos()) max = std::max(c.getKeys().count() + c.getBtns().count(), max);
					priority = max;
				}

			public:
				inline Bind(Trigger mTrigger, Type mType, Mode mMode, const InputFunc& mOn = Internal::getNullInputFunc(), const InputFunc& mOff = Internal::getNullInputFunc())
					: trigger{std::move(mTrigger)}, type{mType}, mode{mMode}, on{mOn}, off{mOff}
				{
					recalculatePriority();
				}

				inline void update(Manager& mManager, FT mFT, InputState& mInputState)	{ isActive(mManager, mInputState) ? on(mFT) : off(mFT); }
				inline void refresh(Manager& mManager, InputState& mInputState)			{ if(!released && !isDown(mManager, mInputState)) released = true; }

				inline void setType(Type mType) noexcept		{ type = mType; }
				inline void setMode(Mode mMode) noexcept		{ mode = mMode; }
				inline void setReleased(bool mValue) noexcept	{ released = mValue; }

				inline bool isActive(Manager& mManager, InputState& mInputState)
				{
					if(type == Type::Always) return isDown(mManager, mInputState);
					if(released && isDown(mManager, mInputState)) { released = false; return true; }
					return false;
				}

				inline bool operator<(const Bind& mRhs) const noexcept	{ return priority > mRhs.priority; }\
		};
	}
}

#endif
