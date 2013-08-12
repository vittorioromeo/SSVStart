// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GLOBAL_TYPEDEFS
#define SSVS_GLOBAL_TYPEDEFS

#include <memory>
#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>

namespace ssvs
{
	using Vec2i = sf::Vector2i;
	using Vec2f = sf::Vector2f;
	using Vec2u = sf::Vector2u;
	using Path = ssvu::FileSystem::Path;
	template<typename T> using Vec2 = sf::Vector2<T>;
	template<typename T, typename TDeleter = std::default_delete<T>> using Uptr = ssvu::Uptr<T, TDeleter>;
}

#endif
