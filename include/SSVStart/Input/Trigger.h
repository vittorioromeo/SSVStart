// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_TRIGGER
#define SSVS_INPUT_TRIGGER

#include <vector>
#include "SSVStart/Input/Combo.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Trigger
		{
			public:
				enum class Type{Continuous, Single};

			private:
				Type type{Type::Continuous};
				std::vector<Combo> combos;
				bool released{true};

				inline bool isDown(GameWindow& mGameWindow) const
				{
					for(const auto& c : combos) if(c.isDown(mGameWindow)) return true;
					return false;
				}

			public:
				Trigger() = default;
				Trigger(const std::initializer_list<Combo>& mCombos) : combos{mCombos} { }

				inline void refresh(GameWindow& mGameWindow)	{ if(!released && !isDown(mGameWindow)) released = true; }
				inline void add(const Combo& mCombo)			{ combos.push_back(mCombo); }

				inline void setType(Type mType)			{ type = mType; }
				inline void setReleased(bool mValue)	{ released = mValue; }

				inline bool isActive(GameWindow& mGameWindow)
				{
					if(type == Type::Continuous) return isDown(mGameWindow);
					if(released && isDown(mGameWindow)) { released = false; return true; }
					return false;
				}

				inline const std::vector<Combo>& getCombos() const { return combos; }
		};
	}
}

#endif
