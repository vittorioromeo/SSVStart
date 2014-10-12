// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SSVUtils/Core/Core.hpp>
#include <SSVUtils/Delegate/Delegate.hpp>

#if SSVS_N_USE_JSON
	#define SSVS_JSON_CNV_FRIEND(...)
#else
	#include <SSVUtilsJson/SSVUtilsJson.hpp>
	#define SSVS_JSON_CNV_FRIEND() SSVUJ_CNV_FRIEND()
#endif

namespace ssvs
{
	using SizeT = ssvu::SizeT;
	using HRClock = ssvu::HRClock;
	using FT = ssvu::FT;
	using FTDuration = ssvu::FTDuration;
	using KKey = sf::Keyboard::Key;
	using MBtn = sf::Mouse::Button;
	constexpr SizeT inputBitOffset{1};
	constexpr SizeT kKeyCount{KKey::KeyCount};
	constexpr SizeT mBtnCount{MBtn::ButtonCount};
	using KeyBitset = std::bitset<kKeyCount + inputBitOffset>; // +offset because it also works with KKey::Unknown, which is -1
	using BtnBitset = std::bitset<mBtnCount + inputBitOffset>; // +offset to stay consistent
	using Path = ssvufs::Path;
	using InputFunc = ssvu::Func<void(FT)>;
	template<typename T, typename TD = ssvu::DefDel<T>> using UPtr = ssvu::UPtr<T, TD>;
	template<typename T> using Vec2 = sf::Vector2<T>;
	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;
	using Vec2u = Vec2<unsigned int>;

	inline auto getKeyBit(KeyBitset& mBitset, KKey mKey) noexcept					{ return mBitset[static_cast<int>(mKey + inputBitOffset)]; }
	inline auto getBtnBit(BtnBitset& mBitset, MBtn mBtn) noexcept					{ return mBitset[static_cast<int>(mBtn + inputBitOffset)]; }
	inline constexpr bool getKeyBit(const KeyBitset& mBitset, KKey mKey) noexcept	{ return mBitset[static_cast<int>(mKey + inputBitOffset)]; }
	inline constexpr bool getBtnBit(const BtnBitset& mBitset, MBtn mBtn) noexcept	{ return mBitset[static_cast<int>(mBtn + inputBitOffset)]; }

	namespace Internal
	{
		inline auto& getNullInputFunc() noexcept { static InputFunc result([](FT){ }); return result; }
	}
}

#endif
