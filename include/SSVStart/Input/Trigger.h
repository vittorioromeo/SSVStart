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
				enum class Types{CONTINUOUS, SINGLE};

			private:
				Types type{Types::CONTINUOUS};
				std::vector<Combo> combos;
				bool released{true};

				bool isDown(GameWindow& mGameWindow);

			public:
				Trigger() = default;
				Trigger(std::initializer_list<Combo> mCombos);

				void addCombo(Combo mCombo);

				bool isActive(GameWindow& mGameWindow);
				void updateRelease(GameWindow& mGameWindow);
				void setType(Types mType);
				void setReleased(bool mValue);
		};
	}
}

#endif
