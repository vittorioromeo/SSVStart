// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVStart/BitmapFont/BitmapFont.h"

using namespace sf;
using namespace ssvu;

namespace ssvs
{
	BitmapFont::BitmapFont(const Texture& mTexture, const BitmapFontData& mData) : texture(mTexture), data(mData) { }

	IntRect BitmapFont::getGlyphRect(char mChar) const
	{
		mChar = mChar - 33 + data.cellStart;
		const auto& i(get2DIndexFrom1D(static_cast<unsigned int>(mChar), data.cellColumns));
		return IntRect(i[0] * data.cellWidth, i[1] * data.cellHeight, data.cellWidth, data.cellHeight);
	}
}
