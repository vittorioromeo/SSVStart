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

				bool isDown(GameWindow& mGameWindow) const;

			public:
				Trigger() = default;
				Trigger(const std::initializer_list<Combo>& mCombos);

				void refresh(GameWindow& mGameWindow);
				inline void add(const Combo& mCombo) { combos.push_back(mCombo); }

				inline void setType(Type mType)			{ type = mType; }
				inline void setReleased(bool mValue)	{ released = mValue; }

				bool isActive(GameWindow& mGameWindow);

				inline const std::vector<Combo>& getCombos() const { return combos; }
		};
	}
}

#endif
