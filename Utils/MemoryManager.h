#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include "Utils.h"

namespace ssvs
{
	namespace Utils
	{
		template<typename T> class MemoryManager
		{
			private:
				std::vector<T*> items, itemsToDel;

			public:
				MemoryManager() = default;
				~MemoryManager() { for(auto& i : items) delete i; }

				template<typename... TArgs> T& create(TArgs&&... mArgs)
				{
					T* result{new T(std::forward<TArgs>(mArgs)...)};
					items.push_back(result);
					return *result;
				}
				void del(T* mItem) { itemsToDel.push_back(mItem); }
				void cleanUp()
				{
					for(auto& i : itemsToDel) { eraseRemove(items, i); delete i; }
					itemsToDel.clear();
				}
				void clear()
				{
					for(auto& i : items) delete i;
					items.clear();
					itemsToDel.clear();
				}
				std::vector<T*>& getItems() { return items; }
		};
	}
}

#endif // MEMORYMANAGER_H
