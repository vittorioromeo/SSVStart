#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTR
#define SSVS_BITMAPTEXT_BTR_IMPL_BTR

#include <SSVUtils/MemoryManager/MemoryManager.hpp>
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include "SSVStart/BitmapText/BTR/Impl/BTREffect.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRChunk.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREWave.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTREColor.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRDrawState.hpp"
#include "SSVStart/BitmapText/BTR/Impl/BTRRoot.hpp"

namespace ssvs
{
namespace BTR
{
    struct Tracking
    {
    };
    struct Leading
    {
    };
    struct HChunkSpacing
    {
    };
    struct Pulse
    {
    };
    struct PulseDef
    {
    };
    using Color = Impl::BTREColor;
    using Wave = Impl::BTREWave;
    using Chunk = Impl::BTRChunk;

    using PtrColor = Ptr<Color>;
    using PtrChunk = Ptr<Chunk>;
    using PtrWave = Ptr<Wave>;
}

using BitmapTextRich = BTR::Impl::BTRRoot;
}

#endif
