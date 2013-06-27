// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_INTERNAL_RESOURCEHOLDER
#define SSVS_ASSETS_INTERNAL_RESOURCEHOLDER

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include "SSVStart/Assets/Internal/Loader.h"

namespace ssvs
{
	namespace Internal
	{
		template<typename T> class ResourceHolder
		{
			private:
				std::unordered_map<std::string, std::unique_ptr<T>> resources;

			public:
				template<typename... TArgs> T& load(const std::string& mId, TArgs&&... mArgs)
				{
					auto inserted(resources.insert(std::make_pair(mId, std::move(Loader<T>::load(mArgs...)))));
					assert(inserted.second); // Assertion error fires if inserting replaced an existing resource
					return *inserted.first->second;
				}

				const T& operator[](const std::string& mId) const
				{
					auto itr(resources.find(mId));
					assert(itr != std::end(resources)); // Assertion error fires if resource id wasn't found
					return *itr->second;
				}
				T& operator[](const std::string& mId)
				{
					return const_cast<T&>(static_cast<const ResourceHolder*>(this)->operator[](mId));
				}

				bool has(const std::string& mId) { return resources.count(mId) > 0; }
				std::unordered_map<std::string, std::unique_ptr<T>>& getResources() { return resources; }
		};
	}
}

#endif
