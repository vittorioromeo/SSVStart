// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_RESOURCEHOLDER
#define SSVS_ASSETS_INTERNAL_RESOURCEHOLDER

#include "SSVStart/Assets/Internal/Loader.hpp"
#include "SSVStart/Assets/Internal/DefaultAssets.hpp"
#include "SSVStart/Assets/Internal/Policies.hpp"

namespace ssvs
{
    namespace Impl
    {
        template <typename T, typename TPolicy>
        class ResourceHolder
        {
            friend struct ssvs::RHPolicyAssert;
            friend struct ssvs::RHPolicyDefault;

        public:
            using ResType = T;
            TPolicy policy;

        private:
            std::vector<std::unique_ptr<T>> ownership;
            std::unordered_map<std::string, T*> resources;

            inline auto& emplaceAndGet(const std::string& mId, T* mPtr)
            {
                const auto& inserted(resources.emplace(mId, mPtr));
                return *inserted.first->second;
            }

        public:
            template <typename... TArgs>
            inline T& load(const std::string& mId, TArgs&&... mArgs)
            {
                SSVU_ASSERT(!has(mId));
                return policy.load(*this, mId, FWD(mArgs)...);
            }

            inline const T& operator[](const std::string& mId) const
            {
                policy.checkMissing(*this, mId);
                return *resources.at(mId);
            }
            inline T& operator[](const std::string& mId)
            {
                policy.checkMissing(*this, mId);
                return *resources[mId];
            }

            inline bool has(const std::string& mId) const noexcept
            {
                return resources.count(mId) > 0;
            }
            inline auto& getResources() noexcept { return resources; }
        };
    }
}

#endif
