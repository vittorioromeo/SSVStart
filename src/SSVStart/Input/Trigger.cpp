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

		void Trigger::refresh(GameWindow& mGameWindow) { if(!isDown(mGameWindow)) released = true; }
		void Trigger::add(Combo mCombo) { combos.push_back(mCombo); }

		void Trigger::setType(Types mType)		{ type = mType; }
		void Trigger::setReleased(bool mValue)	{ released = mValue; }

		bool Trigger::isDown(GameWindow& mGameWindow)
		{
			for(auto& combo : combos) if(combo.isDown(mGameWindow)) return true;
			return false;
		}
		bool Trigger::isActive(GameWindow& mGameWindow)
		{
			switch(type)
			{
				case Types::CONTINUOUS:
					return isDown(mGameWindow);
					break;
				case Types::SINGLE:
					if(released && isDown(mGameWindow)) { released = false; return true; }
					break;
			}

			return false;
		}

	}
}

