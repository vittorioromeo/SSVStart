// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_BITMAPTEXT_BTR_IMPL_PTR
#define SSVS_BITMAPTEXT_BTR_IMPL_PTR

#include "SSVStart/Global/Typedefs.hpp"

#include <cassert>

namespace ssvs {
namespace BTR {
template <typename T>
class Ptr
{
private:
    T* ptr;

public:
#if defined(SSVU_DEBUG)
    inline Ptr() noexcept : ptr{nullptr}
    {}
#else
    inline Ptr() noexcept
    {}
#endif

    inline Ptr(T* mX) noexcept : ptr{mX}
    {}

    inline Ptr(const Ptr&) = default;
    Ptr& operator=(const Ptr&) = default;

    inline auto& operator*() noexcept
    {
        assert(ptr != nullptr);
        return *ptr;
    }
    inline const auto& operator*() const noexcept
    {
        assert(ptr != nullptr);
        return *ptr;
    }
    inline T* operator->() noexcept
    {
        assert(ptr != nullptr);
        return ptr;
    }
    inline T* operator->() const noexcept
    {
        assert(ptr != nullptr);
        return ptr;
    }

    inline operator T*() const noexcept
    {
        return ptr;
    }
};
} // namespace BTR
} // namespace ssvs

#endif
