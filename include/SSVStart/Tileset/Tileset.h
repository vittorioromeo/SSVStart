// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TILESET
#define SSVS_TILESET

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class Tileset
	{
		private:
			Vec2u tileSize;
			std::unordered_map<std::string, Vec2u> labels;

		public:
			Tileset(Vec2u mTileSize);

			Vec2u getIndex(const std::string& mLabel) const;
			sf::IntRect operator[](Vec2u mIndex) const;
			void setLabel(const std::string& mLabel, Vec2u mIndex);
	};
}

#endif
