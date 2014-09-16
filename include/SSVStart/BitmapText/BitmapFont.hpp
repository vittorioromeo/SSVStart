// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPFONT
#define SSVS_BITMAPFONT

namespace ssvs
{
	struct BitmapFontData { unsigned int cellColumns, cellWidth, cellHeight, cellStart; };

	class BitmapFont
	{
		private:
			const sf::Texture& texture;
			const BitmapFontData data;

		public:
			inline BitmapFont(const sf::Texture& mTexture, BitmapFontData mData) : texture(mTexture), data(std::move(mData)) { }

			inline const auto& getTexture() const noexcept	{ return texture; }
			inline auto getCellWidth() const noexcept		{ return data.cellWidth; }
			inline auto getCellHeight() const noexcept		{ return data.cellHeight; }
			inline auto getGlyphRect(char mChar) const
			{
				mChar += data.cellStart - 33;
				const auto& i(ssvu::get2DIdxFrom1D(mChar, data.cellColumns));
				return sf::IntRect(std::get<0>(i) * data.cellWidth, std::get<1>(i) * data.cellHeight, data.cellWidth, data.cellHeight);
			}
	};
}

#endif
