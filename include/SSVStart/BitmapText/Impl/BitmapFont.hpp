// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPFONT
#define SSVS_BITMAPTEXT_IMPL_BITMAPFONT

#include "SSVStart/Global/Typedefs.hpp"

namespace ssvs
{
struct BitmapFontData
{
    unsigned int cellColumns, cellWidth, cellHeight, cellStart;
};

class BitmapFont
{
private:
    const sf::Texture& texture;
    const BitmapFontData data;

public:
    inline BitmapFont(const sf::Texture& mTexture,
    const BitmapFontData& mData) noexcept : texture(mTexture),
                                            data(mData)
    {
    }

    inline const auto& getTexture() const noexcept { return texture; }
    inline auto getCellWidth() const noexcept { return data.cellWidth; }
    inline auto getCellHeight() const noexcept { return data.cellHeight; }
    inline auto getGlyphRect(char mX) const
    {
        mX += toNum<long>(data.cellStart) - 33;
        const auto& i(ssvu::get2DIdxFrom1D(mX, data.cellColumns));
        return sf::IntRect(std::get<0>(i) * data.cellWidth,
        std::get<1>(i) * data.cellHeight, data.cellWidth, data.cellHeight);
    }
};
}

#endif
