// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_INPUTSTATE
#define SSVS_INPUT_INPUTSTATE

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class InputState
		{
			friend ssvs::GameWindow;

			private:
				KeyBitset keys;
				BtnBitset btns;

			public:
				inline KeyBitset::reference operator[](KKey mKey) noexcept { return getKeyBit(keys, mKey); }
				inline BtnBitset::reference operator[](MBtn mBtn) noexcept { return getBtnBit(btns, mBtn); }
				inline bool operator[](KKey mKey) const noexcept { return getKeyBit(keys, mKey); }
				inline bool operator[](MBtn mBtn) const noexcept { return getBtnBit(btns, mBtn); }

				inline void reset() noexcept { keys.reset(); btns.reset(); }

				inline KeyBitset& getKeys() noexcept				{ return keys; }
				inline BtnBitset& getBtns() noexcept				{ return btns; }
				inline const KeyBitset& getKeys() const noexcept	{ return keys; }
				inline const BtnBitset& getBtns() const noexcept	{ return btns; }
		};
	}
}

#endif
