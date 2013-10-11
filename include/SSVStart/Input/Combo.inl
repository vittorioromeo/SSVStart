// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO_INL
#define SSVS_INPUT_COMBO_INL

namespace ssvs
{
	namespace Input
	{
		inline bool Combo::isDown(GameWindow& mGameWindow) const
		{
			if(keys.none() && buttons.none()) return false;
			if((mGameWindow.pressedKeysBitset & keys) != keys) return false;
			if((mGameWindow.pressedButtonsBitset & buttons) != buttons) return false;
			return true;
		}
	}
}

#endif

