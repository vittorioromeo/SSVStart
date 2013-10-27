// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO_INL
#define SSVS_INPUT_COMBO_INL

namespace ssvs
{
	namespace Input
	{
		inline bool Combo::isDown(Manager& mManager, GameWindow& mGameWindow, TriggerMode mMode) const
		{
			// If this combo has no keys or no btns, it is not valid
			if(keys.none() && btns.none()) return false;

			// Check if the combo's keys/btns are currently pressed
			if((mGameWindow.getPressedKeys() & keys) != keys) return false;
			if((mGameWindow.getPressedBtns() & btns) != btns) return false;

			// If the combo is exclusive, check if its keys/btns were pressed previously in this frame
			if(mMode == TriggerMode::Exclusive)
			{
				if((mManager.processedKeys & keys).any()) return false;
				if((mManager.processedBtns & btns).any()) return false;
			}

			// Combo will return true: add its keys/btns to this frame's processed inputs
			mManager.processedKeys |= keys;
			mManager.processedBtns |= btns;

			return true;
		}
	}
}

#endif

