// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_RESOURCEHOLDER
#define SSVS_ASSETS_INTERNAL_RESOURCEHOLDER

#include "SSVStart/Assets/Internal/Loader.hpp"

namespace ssvs
{
	namespace Impl
	{
		template<typename T> class ResourceHolder
		{
			private:
				std::unordered_map<std::string, UPtr<T>> resources;

			public:
				template<typename... TArgs> inline T& load(const std::string& mId, TArgs&&... mArgs)
				{
					SSVU_ASSERT(!has(mId));
					const auto& inserted(resources.emplace(mId, std::move(Loader<T>::load(mArgs...))));
					return *inserted.first->second;
				}

				inline const T& operator[](const std::string& mId) const	{ SSVU_ASSERT(has(mId)); return *resources.at(mId); }
				inline T& operator[](const std::string& mId)				{ SSVU_ASSERT(has(mId)); return *resources[mId]; }

				inline bool has(const std::string& mId) const noexcept	{ return resources.count(mId) > 0; }
				inline decltype(resources)& getResources() noexcept		{ return resources; }
		};
	}
}

#endif
