#ifndef SSVS_UTILS_TRAITS
#define SSVS_UTILS_TRAITS

#include <vector>
#include <google/dense_hash_set>

namespace ssvs
{
	namespace Utils
	{
		namespace Traits
		{
			template<typename TContainer, typename TItem> struct Container
			{
				static void init(TContainer& mContainer);
				static void clear(TContainer& mContainer);
				static void add(TContainer& mContainer, const TItem& mItem);
				static void del(TContainer& mContainer, const TItem& mItem);
			};

			template<typename TItem> struct Container<std::vector<TItem>, TItem>
			{
				typedef std::vector<TItem> TContainer;
				
				static void init(TContainer&) { }
				static void clear(TContainer& mContainer) { mContainer.clear(); }
				static void add(TContainer& mContainer, const TItem& mItem) { mContainer.push_back(mItem); }
				static void del(TContainer& mContainer, const TItem& mItem) { eraseRemove(mContainer, mItem); }
			};

			template<typename TItem> struct Container<google::dense_hash_set<TItem>, TItem>
			{
				typedef google::dense_hash_set<TItem> TContainer;

				static void init(TContainer& mContainer) { mContainer.set_empty_key(nullptr); }
				static void clear(TContainer& mContainer) { mContainer.clear(); }
				static void add(TContainer& mContainer, const TItem& mItem) { mContainer.insert(mItem); }
				static void del(TContainer&, const TItem&) { }
			};
		}
	}
}

#endif
