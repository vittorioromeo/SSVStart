// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Assets/Internal/Loader.hpp"
#include "SSVStart/Assets/Internal/DefaultAssets.hpp"

#include <string>
#include <utility>
#include <memory>
#include <cassert>

namespace ssvs {

struct RHPolicyAssert
{
    template <typename TR, typename... TArgs>
    auto& load(TR& mRH, const std::string& mId, TArgs&&... mArgs)
    {
        using ResType = typename TR::ResType;

        auto uptr(std::move(Impl::Loader<ResType>::load(mArgs...)));
        mRH.ownership.emplace_back(std::move(uptr));
        return mRH.emplaceAndGet(mId, uptr.get());
    }

#ifndef NDEBUG
    template <typename T>
    void checkMissing(T& mRH, const std::string& mId)
    {
        assert(mRH.has(mId));
    }
#else
    template <typename T>
    void checkMissing(T&, const std::string&)
    {}
#endif
};

struct RHPolicyDefault
{
    template <typename TR, typename... TArgs>
    auto& load(TR& mRH, const std::string& mId, TArgs&&... mArgs)
    {
        using ResType = typename TR::ResType;

        auto uptr(std::move(Impl::Loader<ResType>::load(mArgs...)));
        ResType* ptr;

        if(uptr == nullptr)
        {
            ptr = Impl::DefResHelper<ResType>::get();
        }
        else
        {
            ptr = uptr.get();
            mRH.ownership.emplace_back(std::move(uptr));
        }

        return mRH.emplaceAndGet(mId, ptr);
    }

    template <typename T>
    void checkMissing(T& mRH, const std::string& mId)
    {
        using ResType = typename T::ResType;

        if(mRH.has(mId)) return;
        mRH.resources[mId] = Impl::DefResHelper<ResType>::get();
    }
};

} // namespace ssvs
