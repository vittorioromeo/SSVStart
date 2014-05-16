// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <bitset>
#include <memory>
#include <chrono>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SSVUtils/Core/Core.hpp>

#if SSVS_N_USE_JSON
	#define SSVS_JSON_CNV_FRIEND(...)
#else
	#include <SSVUtilsJson/SSVUtilsJson.hpp>
	#define SSVS_JSON_CNV_FRIEND() SSVUJ_CNV_FRIEND()
#endif

namespace ssvs
{
	using HRClock = ssvu::HRClock;
	using FT = ssvu::FT;
	using FTDuration = ssvu::FTDuration;
	using KKey = sf::Keyboard::Key;
	using MBtn = sf::Mouse::Button;
	constexpr std::size_t inputBitOffset{1};
	constexpr std::size_t kKeyCount{KKey::KeyCount};
	constexpr std::size_t mBtnCount{MBtn::ButtonCount};
	using KeyBitset = std::bitset<kKeyCount + inputBitOffset>; // +offset because it also works with KKey::Unknown, which is -1
	using BtnBitset = std::bitset<mBtnCount + inputBitOffset>; // +offset to stay consistent
	using Path = ssvufs::Path;
	using InputFunc = ssvu::Func<void(FT)>;
	template<typename T, typename TDeleter = std::default_delete<T>> using Uptr = ssvu::Uptr<T, TDeleter>;
	template<typename T> using Vec2 = sf::Vector2<T>;
	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;
	using Vec2u = Vec2<unsigned int>;

	inline KeyBitset::reference getKeyBit(KeyBitset& mBitset, KKey mKey) noexcept { return mBitset[static_cast<int>(mKey + inputBitOffset)]; }
	inline BtnBitset::reference getBtnBit(BtnBitset& mBitset, MBtn mBtn) noexcept { return mBitset[static_cast<int>(mBtn + inputBitOffset)]; }
	inline constexpr bool getKeyBit(const KeyBitset& mBitset, KKey mKey) noexcept { return mBitset[static_cast<int>(mKey + inputBitOffset)]; }
	inline constexpr bool getBtnBit(const BtnBitset& mBitset, MBtn mBtn) noexcept { return mBitset[static_cast<int>(mBtn + inputBitOffset)]; }

	namespace Internal
	{
		inline const InputFunc& getNullInputFunc() noexcept
		{
			static InputFunc result([](FT){ });
			return result;
		}
	}
}

#endif
