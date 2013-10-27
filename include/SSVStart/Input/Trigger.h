// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_TRIGGER
#define SSVS_INPUT_TRIGGER

#include <vector>
#include "SSVStart/Input/Enums.h"
#include "SSVStart/Input/Combo.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Manager;

		class Trigger
		{
			private:
				TriggerType type{TriggerType::Always};
				TriggerMode mode{TriggerMode::Overlap};
				std::vector<Combo> combos;
				bool released{true};

				inline bool isDown(Manager& mManager, GameWindow& mGameWindow) const
				{
					for(const auto& c : combos) if(c.isDown(mManager, mGameWindow, mode)) return true;
					return false;
				}

			public:
				Trigger() = default;
				Trigger(const std::initializer_list<Combo>& mCombos) : combos{mCombos} { }

				inline void refresh(Manager& mManager, GameWindow& mGameWindow)	{ if(!released && !isDown(mManager, mGameWindow)) released = true; }

				inline void setType(TriggerType mType)	noexcept	{ type = mType; }
				inline void setMode(TriggerMode mMode) noexcept		{ mode = mMode; }
				inline void setReleased(bool mValue) noexcept		{ released = mValue; }

				inline bool isActive(Manager& mManager, GameWindow& mGameWindow)
				{
					if(type == TriggerType::Always) return isDown(mManager, mGameWindow);
					if(released && isDown(mManager, mGameWindow)) { released = false; return true; }
					return false;
				}

				inline decltype(combos)& getCombos() noexcept				{ return combos; }
				inline const decltype(combos)& getCombos() const noexcept	{ return combos; }
		};
	}
}

#endif
