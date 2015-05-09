// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_BIND
#define SSVS_INPUT_BIND

namespace ssvs
{
	namespace Input
	{
		class InputState;
		class Manager;

		class Bind
		{
			private:
				Manager& manager;
				Trigger trigger;
				InputFunc on, off;
				SizeT priorityCombo{0u}; // Priority calculated automatically
				SizeT priorityUser{0u}; // Priority set by user
				Type type{Type::Always};
				Mode mode{Mode::Overlap};
				bool released{true};

				inline bool isDown(InputState& mInputState) const
				{
					for(const auto& c : trigger.getCombos()) if(c.isDown(manager, mInputState, mode)) return true;
					return false;
				}

				inline void recalculatePriorityCombo()
				{
					SizeT max{0u};
					for(auto& c : trigger.getCombos()) max = std::max(c.getKeys().count() + c.getBtns().count(), max);
					priorityCombo = max;
				}

			public:
				inline Bind(Manager& mManager, Trigger mTrigger, Type mType, Mode mMode, const InputFunc& mOn = Impl::getNullInputFunc(), const InputFunc& mOff = Impl::getNullInputFunc())
					: manager(mManager), trigger{ssvu::mv(mTrigger)}, on{mOn}, off{mOff}, type{mType}, mode{mMode}
				{
					recalculatePriorityCombo();
				}

				inline void update(FT mFT, InputState& mInputState)	{ isActive(mInputState) ? on(mFT) : off(mFT); }
				inline void refresh(InputState& mInputState)		{ if(!released && !isDown(mInputState)) released = true; }

				inline void setType(Type mType) noexcept		{ type = mType; }
				inline void setMode(Mode mMode) noexcept		{ mode = mMode; }
				inline void setReleased(bool mValue) noexcept	{ released = mValue; }

				inline bool isActive(InputState& mInputState)
				{
					if(type == Type::Always) return isDown(mInputState);
					if(released && isDown(mInputState)) { released = false; return true; }
					return false;
				}

				inline bool operator<(const Bind& mRhs) const noexcept
				{
					// User-defined priority takes precendence
					if(priorityUser != mRhs.priorityUser) return priorityCombo > mRhs.priorityCombo;

					return priorityUser < mRhs.priorityUser;
				}

				void setPriorityUser(SizeT mValue) noexcept;
		};
	}
}

#endif
