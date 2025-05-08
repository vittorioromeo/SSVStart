// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Assets/Internal/Loader.hpp"
#include "SSVStart/Assets/Internal/DefaultAssets.hpp"
#include "SSVStart/Assets/Internal/Policies.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>

namespace ssvs::Impl {

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

    auto& emplaceAndGet(const std::string& mId, T* mPtr)
    {
        const auto& inserted(resources.emplace(mId, mPtr));
        return *inserted.first->second;
    }

public:
    template <typename... TArgs>
    T& load(const std::string& mId, TArgs&&... mArgs)
    {
        assert(!has(mId));
        return policy.load(*this, mId, FWD(mArgs)...);
    }

    const T& operator[](const std::string& mId) const
    {
        policy.checkMissing(*this, mId);
        return *resources.at(mId);
    }

    T& operator[](const std::string& mId)
    {
        policy.checkMissing(*this, mId);
        return *resources[mId];
    }

    bool has(const std::string& mId) const noexcept
    {
        return resources.count(mId) > 0;
    }

    auto& getResources() noexcept
    {
        return resources;
    }
};

} // namespace ssvs::Impl
