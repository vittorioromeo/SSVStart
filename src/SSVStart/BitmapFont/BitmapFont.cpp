// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/BitmapFont/BitmapFont.h"

using namespace sf;

namespace ssvs
{
	BitmapFont::BitmapFont(const Texture& mTexture, const BitmapFontData& mData) : texture(mTexture), data(mData) { }

	const Texture& BitmapFont::getTexture() const	{ return texture; }
	unsigned int BitmapFont::getCellWidth() const	{ return data.cellWidth; }
	unsigned int BitmapFont::getCellHeight() const	{ return data.cellHeight; }

	IntRect BitmapFont::getGlyphRect(char mChar) const
	{
		mChar = mChar - 33 + data.cellStart;
		unsigned int y{mChar / data.cellColumns};
		unsigned int x{mChar - y * data.cellColumns};

		return IntRect(x * data.cellWidth, y * data.cellHeight, data.cellWidth, data.cellHeight);
	}
}
