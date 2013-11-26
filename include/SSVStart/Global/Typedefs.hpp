// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <bitset>
#include <memory>
#include <chrono>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SSVUtils/Global/Typedefs.hpp>
#include <SSVUtils/FileSystem/FileSystem.hpp>

namespace ssvs
{
	using HRClock = ssvu::HRClock;
	using FT = ssvu::FT;
	using FTDuration = ssvu::FTDuration;
	using KKey = sf::Keyboard::Key;
	using MBtn = sf::Mouse::Button;
	constexpr std::size_t KKeyCount{KKey::KeyCount};
	constexpr std::size_t MBtnCount{MBtn::ButtonCount};
	using KeyBitset = std::bitset<KKeyCount + 1>; // +1 because it also works with KKey::Unknown, which is -1
	using BtnBitset = std::bitset<MBtnCount + 1>; // +1 to stay consistent
	using Path = ssvu::FileSystem::Path;
	using InputFunc = ssvu::Func<void(FT)>;
	template<typename T, typename TDeleter = std::default_delete<T>> using Uptr = ssvu::Uptr<T, TDeleter>;
	template<typename T> using Vec2 = sf::Vector2<T>;
	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;
	using Vec2u = Vec2<unsigned int>;
}

#endif
