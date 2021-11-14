// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTRDRAWSTATE
#define SSVS_BITMAPTEXT_BTR_IMPL_BTRDRAWSTATE

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREColor.hpp"

namespace ssvs
{
namespace BTR
{
namespace Impl
{
struct BTRDrawState
{
    struct RowData
    {
        float width;
        std::size_t cells;

        inline RowData(float mWidth, std::size_t mCells) noexcept
            : width{mWidth}, cells{mCells}
        {
        }
    };

    std::vector<RowData> rDatas;
    float xMin, xMax, yMin, yMax, nextHChunkSpacing;
    std::size_t width, height, iX;
    int nl, htab, vtab;

    inline void reset(const BitmapFont& mBF) noexcept
    {
        rDatas.clear();

        xMin = xMax = yMin = yMax = nextHChunkSpacing = 0.f;

        width = mBF.getCellWidth();
        height = mBF.getCellHeight();
        iX = 0;

        nl = htab = vtab = 0;
    }
};
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
