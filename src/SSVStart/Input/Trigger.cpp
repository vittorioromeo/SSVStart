// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Input/Trigger.h"

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

		void Trigger::updateRelease(GameWindow& mGameWindow) { if(!isDown(mGameWindow)) released = true; }

		bool Trigger::isActive(GameWindow& mGameWindow)
		{
			if(released && type == Types::SINGLE) 
			{ 
				if(isDown(mGameWindow))
				{ 
					released = false; 
					return true; 
				} 
			}
			else if(type == Types::CONTINUOUS) return isDown(mGameWindow);
			return false;
		}
		void Trigger::setType(Types mType) { type = mType; }
		void Trigger::setReleased(bool mValue) { released = mValue; }
	}
}

