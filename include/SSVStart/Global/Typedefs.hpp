// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include <SSVUtils/Core/Common/Casts.hpp>
#include <SSVUtils/Core/Common/Frametime.hpp>
#include <SSVUtils/Core/FileSystem/FileSystem.hpp>

#include <bitset>

namespace ssvs
{
    using ssvu::FT;
    using ssvu::FTDuration;
    using ssvufs::Path;

    using ssvu::toNum;
    using ssvu::toInt;
    using ssvu::toFloat;

    using KKey = sf::Keyboard::Key;
    using MBtn = sf::Mouse::Button;

    constexpr std::size_t inputBitOffset{1};
    constexpr std::size_t fingerCount{16};
    constexpr std::size_t kKeyCount{KKey::KeyCount};
    constexpr std::size_t mBtnCount{MBtn::ButtonCount};
    constexpr std::size_t jBtnCount{sf::Joystick::ButtonCount};

    using FingerID = unsigned int;
    using FingerBitset = std::bitset<fingerCount>;
    using KeyBitset =
        std::bitset<kKeyCount +
                    inputBitOffset>; // +offset because it also works with
                                     // KKey::Unknown, which is -1
    using BtnBitset =
        std::bitset<mBtnCount + inputBitOffset>; // +offset to stay consistent
    using InputFunc = std::function<void(FT)>;

    template <typename T>
    using Vec2 = sf::Vector2<T>;
    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;
    using Vec2u = Vec2<unsigned int>;

    inline auto getFingerBit(FingerBitset& mBitset, FingerID mI) noexcept
    {
        return mBitset[mI];
    }
    inline constexpr bool getFingerBit(
        const FingerBitset& mBitset, FingerID mI) noexcept
    {
        return mBitset[mI];
    }
    inline auto getKeyBit(KeyBitset& mBitset, KKey mKey) noexcept
    {
        return mBitset[toInt(mKey + inputBitOffset)];
    }
    inline auto getBtnBit(BtnBitset& mBitset, MBtn mBtn) noexcept
    {
        return mBitset[toInt(mBtn + inputBitOffset)];
    }
    inline constexpr bool getKeyBit(
        const KeyBitset& mBitset, KKey mKey) noexcept
    {
        return mBitset[toInt(mKey + inputBitOffset)];
    }
    inline constexpr bool getBtnBit(
        const BtnBitset& mBitset, MBtn mBtn) noexcept
    {
        return mBitset[toInt(mBtn + inputBitOffset)];
    }

    namespace Impl
    {
        inline auto& getNullInputFunc() noexcept
        {
            static InputFunc result([](FT)
                {
                });
            return result;
        }
    }
}

#endif
