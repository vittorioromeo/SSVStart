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
			if(keys.empty() && buttons.empty()) return false;
			for(const auto& k : keys) if(!mGameWindow.isKeyPressed(k)) return false;
			for(const auto& b : buttons) if(!mGameWindow.isButtonPressed(b)) return false;
			return true;
		}
	}
}

#endif

