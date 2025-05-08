// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_IMPL_BITMAPTEXTDRAWSTATE
#define SSVS_BITMAPTEXT_IMPL_BITMAPTEXTDRAWSTATE

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include <SFML/Graphics/Color.hpp>

namespace ssvs {
namespace Impl {
struct BitmapTextDrawState
{
    sf::Color colorFG{sf::Color::White};
    float xMin, xMax, yMin, yMax;
    float tracking{0.f};
    unsigned int iX, iY, width, height, chCount;

    inline void reset(const BitmapFont& mBF)
    {
        xMin = xMax = yMin = yMax = 0;
        iX = iY = chCount = 0;
        width = mBF.getCellWidth();
        height = mBF.getCellHeight();
    }
};
} // namespace Impl

enum class TextAlign : int
{
    Left = 0,
    Center = 1,
    Right = 2
};
} // namespace ssvs

#endif
