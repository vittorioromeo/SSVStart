// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TILESET
#define SSVS_TILESET

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class Tileset
	{
		private:
			sf::Vector2u tileSize;
			std::unordered_map<std::string, sf::Vector2u> labels;

		public:
			Tileset(sf::Vector2u mTileSize);

			sf::Vector2u getIndex(const std::string& mLabel) const;
			sf::IntRect operator[](sf::Vector2u mIndex) const;
			void setLabel(const std::string& mLabel, sf::Vector2u mIndex);
	};
}

#endif
