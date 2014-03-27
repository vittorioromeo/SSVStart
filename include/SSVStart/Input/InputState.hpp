// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_INPUTSTATE
#define SSVS_INPUT_INPUTSTATE

#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class InputState
		{
			friend class ssvs::GameWindow;

			private:
				KeyBitset pressedKeys;
				BtnBitset pressedBtns;

				inline void setKeyPressed(KKey mKey, bool mValue) noexcept { getKeyBit(pressedKeys, mKey) = mValue; }
				inline void setBtnPressed(MBtn mBtn, bool mValue) noexcept { getBtnBit(pressedBtns, mBtn) = mValue; }

			public:
				inline bool isKeyPressed(KKey mKey) const noexcept		{ return getKeyBit(pressedKeys, mKey); }
				inline bool isBtnPressed(MBtn mBtn) const noexcept		{ return getBtnBit(pressedBtns, mBtn); }
				inline const KeyBitset& getPressedKeys() const noexcept	{ return pressedKeys; }
				inline const BtnBitset& getPressedBtns() const noexcept	{ return pressedBtns; }
		};
	}
}

#endif
