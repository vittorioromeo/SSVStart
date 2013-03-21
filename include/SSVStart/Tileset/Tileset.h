// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TILESET
#define SSVS_TILESET

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class Tileset
	{
		private:
			sf::Vector2i tileSize;
			std::map<std::string, sf::Vector2i> labels;

		public:
			Tileset(sf::Vector2i mTileSize);

			sf::Sprite getSprite(int mX, int mY, const sf::Texture& mTexture);
			sf::Sprite getSprite(const std::string& mLabel, const sf::Texture& mTexture);

			sf::IntRect getTextureRect(int mX, int mY);
			sf::IntRect getTextureRect(const std::string& mLabel);

			void setLabel(const std::string& mLabel, int mIndexX, int mIndexY);
	};
}

#endif
