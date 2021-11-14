// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTRCHUNK_INL
#define SSVS_BITMAPTEXT_BTR_IMPL_BTRCHUNK_INL

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/Ptr.hpp"
#include "SSVStart/BitmapText/BTR/Impl/Fwd.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREColor.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRDrawState.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRRoot.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTR.hpp"

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include <SSVUtils/Core/Utils/Math.hpp>


namespace ssvs
{
namespace BTR
{
namespace Impl
{
template <typename TF>
inline void BTRChunk::forVertices(TF mFn) noexcept
{
    auto count(idxHierarchyEnd - idxHierarchyBegin);

    for(auto i(0u); i < count; ++i)
        mFn(i, count, root.vertices[idxHierarchyBegin + i],
            root.verticesOriginal[idxHierarchyBegin + i]);
}

inline void BTRChunk::refreshGeometry() noexcept
{
    root.mkVertices(*this);

    for(auto& c : children)
        if(c->enabled)
        {
            c->refreshGeometry();

            ssvu::clampMax(idxHierarchyBegin, c->idxHierarchyBegin);
            ssvu::clampMin(idxHierarchyEnd, c->idxHierarchyEnd);
        }
}
inline void BTRChunk::refreshEffects() noexcept
{
    if(parent != nullptr && parent->enabled)
        for(auto& e : parent->childrenEffects) e->apply(*this);

    for(auto& c : children)
        if(c->enabled) c->refreshEffects();
}

template <typename... TArgs>
inline BTRChunk& BTRChunk::mkChild(TArgs&&... mArgs)
{
    auto& result(root.mkChunk(FWD(mArgs)...));
    result.parent = this;
    children.emplace_back(&result);
    return result;
}
template <typename T, typename... TArgs>
inline T& BTRChunk::mkEffect(TArgs&&... mArgs)
{
    auto& result(root.mkEffect<T>(FWD(mArgs)...));
    childrenEffects.emplace_back(&result);
    return result;
}

template <typename T>
inline auto& BTRChunk::in(T&& mStr)
{
    auto& result(mkChild());
    result.str = FWD(mStr);

    root.mustRefreshGeometry = true;
    return result;
}
inline auto& BTRChunk::in(Ptr<Chunk>& mPtr)
{
    auto& result(in(""));
    mPtr = &result;
    return result;
}
template <typename T>
inline auto& BTRChunk::in(Ptr<Chunk>& mPtr, T&& mStr)
{
    auto& result(in(FWD(mStr)));
    mPtr = &result;
    return result;
}
inline auto& BTRChunk::in()
{
    return in("");
}

template <typename T>
inline auto& BTRChunk::mk(T&& mStr)
{
    in(FWD(mStr));
    return *this;
}
template <typename T>
inline auto& BTRChunk::mk(Ptr<Chunk>& mPtr, T&& mStr)
{
    in(mPtr, FWD(mStr));
    return *this;
}
inline auto& BTRChunk::mk(Ptr<Chunk>& mPtr)
{
    in(mPtr, "");
    return *this;
}

inline auto& BTRChunk::eff(const sf::Color& mX)
{
    mkEffect<BTREColor>(mX);
    return *this;
}
template <typename T, typename... TArgs>
inline auto& BTRChunk::eff(TArgs&&... mArgs)
{
    EffectHelper<T>::mk(*this, FWD(mArgs)...);
    return *this;
}
template <typename T, typename... TArgs>
inline auto& BTRChunk::eff(Ptr<T>& mPtr, TArgs&&... mArgs)
{
    mPtr = &EffectHelper<T>::mk(*this, FWD(mArgs)...);
    return *this;
}

template <typename T>
inline void BTRChunk::setStr(T&& mX)
{
    str = FWD(mX);
    root.mustRefreshGeometry = true;
}
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
