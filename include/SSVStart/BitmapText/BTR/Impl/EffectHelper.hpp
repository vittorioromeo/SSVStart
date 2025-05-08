// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_EFFECTHELPER
#define SSVS_BITMAPTEXT_BTR_IMPL_EFFECTHELPER

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREColor.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRDrawState.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRRoot.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTR.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.inl"

namespace ssvs {
namespace BTR {
namespace Impl {
template <typename T>
struct EffectHelper
{
    template <typename... TArgs>
    inline static auto& mk(BTRChunk& mC, TArgs&&... mArgs)
    {
        return mC.mkEffect<T>(FWD(mArgs)...);
    }
};
template <>
struct EffectHelper<Tracking>
{
    inline static void mk(BTRChunk& mC, float mX)
    {
        mC.modTracking = mX;
        mC.root.mustRefreshGeometry = true;
    }
};
template <>
struct EffectHelper<Leading>
{
    inline static void mk(BTRChunk& mC, float mX)
    {
        mC.modLeading = mX;
        mC.root.mustRefreshGeometry = true;
    }
};
template <>
struct EffectHelper<HChunkSpacing>
{
    inline static void mk(BTRChunk& mC, float mX)
    {
        mC.modHChunkSpacing = mX;
        mC.root.mustRefreshGeometry = true;
    }
};
template <>
struct EffectHelper<Pulse>
{
    inline static auto& mk(BTRChunk& mC, const sf::Color& mColor, float mSpeed,
        float mMax, float mStart)
    {
        auto& result(mC.mkEffect<Color>(mColor));
        result.setAnimPulse(mSpeed, mMax, mStart);
        return result;
    }
};
template <>
struct EffectHelper<PulseDef>
{
    inline static auto& mk(BTRChunk& mC, const sf::Color& mColor)
    {
        return mC.eff<Pulse>(mColor, 0.05f, 110.f, 0.f);
    }
};
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
