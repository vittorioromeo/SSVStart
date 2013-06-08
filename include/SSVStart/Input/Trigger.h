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
				Trigger(std::initializer_list<Combo> mCombos);

				void refresh(GameWindow& mGameWindow);
				void add(Combo mCombo);

				void setType(Type mType);
				void setReleased(bool mValue);

				bool isActive(GameWindow& mGameWindow);
		};
	}
}

#endif
