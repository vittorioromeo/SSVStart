// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_POLICIES
#define SSVS_ASSETS_INTERNAL_POLICIES

#include "SSVStart/Assets/Internal/Loader.hpp"
#include "SSVStart/Assets/Internal/DefaultAssets.hpp"

namespace ssvs
{
    struct RHPolicyAssert
    {
        template <typename TR, typename... TArgs>
        inline auto& load(TR& mRH, const std::string& mId, TArgs&&... mArgs)
        {
            using ResType = typename TR::ResType;

            auto uptr(ssvu::mv(Impl::Loader<ResType>::load(mArgs...)));
            mRH.ownership.emplace_back(ssvu::mv(uptr));
            return mRH.emplaceAndGet(mId, uptr.get());
        }

#if defined(SSVU_ASSERT_IS_ENABLED)
        template <typename T>
        inline void checkMissing(T& mRH, const std::string& mId)
        {
            SSVU_ASSERT(mRH.has(mId));
        }
#else
        template <typename T>
        inline void checkMissing(T&, const std::string&)
        {
        }
#endif
    };

    struct RHPolicyDefault
    {
        template <typename TR, typename... TArgs>
        inline auto& load(TR& mRH, const std::string& mId, TArgs&&... mArgs)
        {
            using ResType = typename TR::ResType;

            auto uptr(ssvu::mv(Impl::Loader<ResType>::load(mArgs...)));
            ResType* ptr;

            if(uptr == nullptr)
            {
                ptr = Impl::DefResHelper<ResType>::get();
            }
            else
            {
                ptr = uptr.get();
                mRH.ownership.emplace_back(ssvu::mv(uptr));
            }

            return mRH.emplaceAndGet(mId, ptr);
        }

        template <typename T>
        inline void checkMissing(T& mRH, const std::string& mId)
        {
            using ResType = typename T::ResType;

            if(mRH.has(mId)) return;
            mRH.resources[mId] = Impl::DefResHelper<ResType>::get();
        }
    };
}

#endif
