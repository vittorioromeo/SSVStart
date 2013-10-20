// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <bitset>
#include <memory>
#include <SFML/System.hpp>
#include <SSVUtils/Global/Typedefs.h>
#include <SSVUtils/FileSystem/FileSystem.h>

namespace ssvs
{
	using KKey = sf::Keyboard::Key;
	using MBtn = sf::Mouse::Button;
	constexpr std::size_t KKeyCount{KKey::KeyCount};
	constexpr std::size_t MBtnCount{MBtn::ButtonCount};
	using KeyBitset = std::bitset<KKeyCount + 1>; // +1 because it also works with KKey::Unknown, which is -1
	using BtnBitset = std::bitset<MBtnCount + 1>; // +1 to stay consistent
	using Vec2i = sf::Vector2i;
	using Vec2f = sf::Vector2f;
	using Vec2u = sf::Vector2u;
	using Path = ssvu::FileSystem::Path;
	using InputFunc = ssvu::Func<void(float)>;
	template<typename T> using Vec2 = sf::Vector2<T>;
	template<typename T, typename TDeleter = std::default_delete<T>> using Uptr = ssvu::Uptr<T, TDeleter>;
}

#endif
