// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_BTREFFECT
#define SSVS_BITMAPTEXT_BTR_IMPL_BTREFFECT

#include "SSVStart/BitmapText/BTR/Impl/Fwd.hpp"
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"

#include <SSVUtils/MemoryManager/MemoryManager.hpp>

namespace ssvs {
namespace BTR {
namespace Impl {
class BTREffect
{
    friend class BTR::Impl::BTRRoot;

public:
    inline virtual ~BTREffect()
    {}

    inline virtual void update(float) noexcept
    {}
    inline virtual void apply(BTRChunk&) noexcept
    {}
};
} // namespace Impl
} // namespace BTR
} // namespace ssvs

#endif
