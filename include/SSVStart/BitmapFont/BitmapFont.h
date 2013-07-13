// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPFONT
#define SSVS_BITMAPFONT

#include <SFML/Graphics.hpp>
#include "SSVStart/BitmapFont/BitmapFontData.h"

namespace ssvs
{
	class BitmapFont
	{
		private:
			const sf::Texture& texture;
			const BitmapFontData data;

		public:
			BitmapFont(const sf::Texture& mTexture, const BitmapFontData& mData);

			inline const sf::Texture& getTexture() const	{ return texture; }
			inline unsigned int getCellWidth() const		{ return data.cellWidth; }
			inline unsigned int getCellHeight() const		{ return data.cellHeight; }
			sf::IntRect getGlyphRect(char mChar) const;
	};
}

#endif
