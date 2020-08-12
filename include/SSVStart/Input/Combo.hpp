// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO
#define SSVS_INPUT_COMBO

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
            inline Combo() = default;
            inline Combo(const std::initializer_list<KKey>& mKeys,
                const std::initializer_list<MBtn>& mBtns = {})
            {
                for(const KKey& k : mKeys) addKey(k);
                for(const MBtn& b : mBtns) addBtn(b);
            }
            inline Combo(const std::initializer_list<MBtn>& mBtns)
                : Combo{{}, mBtns}
            {
            }

            inline bool operator==(const Combo& mRhs) const noexcept
            {
                return keys == mRhs.keys && btns == mRhs.btns;
            }
            inline bool operator!=(const Combo& mRhs) const noexcept
            {
                return !this->operator==(mRhs);
            }

            bool isDown(
                Manager& mManager, InputState& mInputState, Mode mMode) const;

            inline void addKey(KKey mKey) noexcept
            {
                getKeyBit(keys, mKey) = true;
                if(mKey != KKey::Unknown)
                    getKeyBit(keys, KKey::Unknown) = false;
            }
            inline void addBtn(MBtn mBtn) noexcept
            {
                getBtnBit(btns, mBtn) = true;
                getKeyBit(keys, KKey::Unknown) = false;
            }
            inline void clearBind()
            {
                for(auto i(0u); i < kKeyCount; ++i)
                    getKeyBit(keys, KKey(i)) = false;
                for(auto j(0u); j < mBtnCount; ++j)
                    getBtnBit(btns, MBtn(j)) = false;
    
                getKeyBit(keys, KKey::Unknown) = true; //mark as unbound
            }
            inline bool isUnbound() const
            {
                return getKeyBit(keys, KKey::Unknown) == true;
            }

            inline const auto& getKeys() const noexcept { return keys; }
            inline const auto& getBtns() const noexcept { return btns; }
        };
    }
}

#endif
