// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO
#define SSVS_INPUT_COMBO

#include <bitset>
#include <vector>
#include <SFML/Window.hpp>

namespace ssvs
{
	namespace Input
	{
		class InputState;
		class Manager;

		class Combo
		{
			private:
				KeyBitset keys;
				BtnBitset btns;

			public:
				Combo() = default;
				Combo(const std::initializer_list<KKey>& mKeys, const std::initializer_list<MBtn>& mBtns = {})
				{
					for(const auto& k : mKeys) addKey(k);
					for(const auto& b : mBtns) addBtn(b);
				}
				Combo(const std::initializer_list<MBtn>& mBtns) : Combo{{}, mBtns} { }

				bool isDown(Manager& mManager, InputState& mInputState, Mode mMode) const;

				inline void addKey(KKey mKey) { getKeyBit(keys, mKey) = true; }
				inline void addBtn(MBtn mBtn) { getBtnBit(btns, mBtn) = true; }

				inline const KeyBitset& getKeys() const noexcept { return keys; }
				inline const BtnBitset& getBtns() const noexcept { return btns; }
		};
	}
}

#endif
