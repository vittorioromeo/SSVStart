#ifndef SSVS_UTILS_MEMORYMANAGER
#define SSVS_UTILS_MEMORYMANAGER

#include "Utils.h"
#include "Traits/Traits.h"

namespace ssvs
{
	namespace Utils
	{
		template<typename TItem, typename TContainer = std::vector<TItem*>, typename TDelContainer = std::vector<TItem*>> class MemoryManager
		{
			private:
				typedef Traits::Container<TContainer, TItem*> ContainerTraits;
				typedef Traits::Container<TDelContainer, TItem*> DelContainerTraits;

				TContainer items;
				TDelContainer itemsToDel;

			public:
				MemoryManager() { ContainerTraits::init(items); DelContainerTraits::init(itemsToDel); }
				~MemoryManager() { for(auto& i : items) delete i; }

				template<typename TItemType, typename... TArgs> TItemType& create(TArgs&&... mArgs)
				{
					TItemType* result{new TItemType(std::forward<TArgs>(mArgs)...)};
					ContainerTraits::add(items, static_cast<TItem*>(result)); return *result;
				}
				template<typename... TArgs> TItem& create(TArgs&&... mArgs)
				{
					TItem* result{new TItem(std::forward<TArgs>(mArgs)...)};
					ContainerTraits::add(items, result); return *result;
				}
				void del(TItem* mItem) { DelContainerTraits::add(itemsToDel, mItem); }
				void cleanUp()
				{
					for(auto& i : itemsToDel) { ContainerTraits::del(items, i); delete i; }
					DelContainerTraits::clear(itemsToDel);
				}
				void clear()
				{
					for(auto& i : items) delete i;
					ContainerTraits::clear(items);
					DelContainerTraits::clear(itemsToDel);
				}
				TContainer& getItems() { return items; }
		};
	}
}

#endif
