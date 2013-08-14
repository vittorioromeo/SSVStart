// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPFONT
#define SSVS_BITMAPFONT

#include <SFML/Graphics.hpp>
#include <SSVUtils/SSVUtils.h>

namespace ssvs
{
	struct BitmapFontData { unsigned int cellColumns, cellWidth, cellHeight, cellStart; };

	class BitmapFont
	{
		private:
			const sf::Texture& texture;
			const BitmapFontData data;

		public:
			BitmapFont(const sf::Texture& mTexture, const BitmapFontData& mData) : texture(mTexture), data(mData) { }

			inline const sf::Texture& getTexture() const	{ return texture; }
			inline unsigned int getCellWidth() const		{ return data.cellWidth; }
			inline unsigned int getCellHeight() const		{ return data.cellHeight; }
			inline sf::IntRect getGlyphRect(char mChar) const
			{
				mChar = mChar - 33 + data.cellStart;
				const auto& i(ssvu::get2DIndexFrom1D(static_cast<unsigned int>(mChar), data.cellColumns));
				return sf::IntRect(i[0] * data.cellWidth, i[1] * data.cellHeight, data.cellWidth, data.cellHeight);
			}
	};
}

#endif
