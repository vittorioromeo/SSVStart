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
			sf::Vector2i tileSize;
			std::unordered_map<std::string, sf::Vector2i> labels;

		public:
			Tileset(sf::Vector2i mTileSize);

			sf::IntRect getRect(int mX, int mY) const;
			sf::IntRect getRect(const std::string& mLabel) const;

			sf::IntRect operator[](const std::string& mLabel) const;

			void setLabel(const std::string& mLabel, int mIndexX, int mIndexY);
	};
}

#endif
