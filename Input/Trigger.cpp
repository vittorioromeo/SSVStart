#include "Trigger.h"

using namespace sf;
using namespace std;

namespace ssvs
{
	namespace Input
	{
		Trigger::Trigger(initializer_list<Combo> mCombos) : combos{mCombos} { }

		bool Trigger::isDown(GameWindow& mGameWindow)
		{
			for(auto& combo : combos) if(combo.isDown(mGameWindow)) return true;
			return false;
		}

		void Trigger::updateRelease(GameWindow& mGameWindow) { released = !isDown(mGameWindow); }

		bool Trigger::isActive(GameWindow& mGameWindow)
		{
			if(type == Types::SINGLE) return released && isDown(mGameWindow);
			else if(type == Types::CONTINUOUS) return isDown(mGameWindow);
			return false;
		}
		void Trigger::setType(Types mType) { type = mType; }
		void Trigger::setReleased(bool mValue) { released = mValue; }
	}
}

