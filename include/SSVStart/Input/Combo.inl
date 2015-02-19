// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO_INL
#define SSVS_INPUT_COMBO_INL

namespace ssvs
{
	namespace Input
	{
		inline bool Combo::isDown(Manager& mManager, InputState& mInputState, Mode mMode) const
		{
			// If this combo has no keys or no btns, it is not valid
			if(keys.none() && btns.none()) return false;

			// Check if the combo's keys/btns are currently pressed
			if((mInputState.getKeys() & keys) != keys) return false;
			if((mInputState.getBtns() & btns) != btns) return false;

			// If the combo is exclusive, check if its keys/btns were pressed previously in this frame
			if(mMode == Mode::Exclusive)
			{
				if((mManager.processedInput.getKeys() & keys).any()) return false;
				if((mManager.processedInput.getBtns() & btns).any()) return false;
			}

			// Combo will return true: add its keys/btns to this frame's processed inputs
			mManager.processedInput.getKeys() |= keys;
			mManager.processedInput.getBtns() |= btns;

			return true;
		}
	}
}

#endif

