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
		Trigger::Trigger(const initializer_list<Combo>& mCombos) : combos{mCombos} { }

		void Trigger::refresh(GameWindow& mGameWindow) { if(!isDown(mGameWindow)) released = true; }

		bool Trigger::isDown(GameWindow& mGameWindow) const
		{
			for(const auto& c : combos) if(c.isDown(mGameWindow)) return true;
			return false;
		}
		bool Trigger::isActive(GameWindow& mGameWindow)
		{
			switch(type)
			{
				case Type::Continuous:
					return isDown(mGameWindow);
					break;
				case Type::Single:
					if(released && isDown(mGameWindow)) { released = false; return true; }
					break;
			}

			return false;
		}

	}
}

