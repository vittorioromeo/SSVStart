#ifndef SSVS_INPUT_TRIGGER
#define SSVS_INPUT_TRIGGER

#include <vector>
#include "Input/Combo.h"

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
				Trigger(std::initializer_list<Combo> mCombos);

				bool isActive(GameWindow& mGameWindow);
				void updateRelease(GameWindow& mGameWindow);
				void setType(Types mType);
				void setReleased(bool mValue);
		};
	}
}

#endif
