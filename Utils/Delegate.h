// Thanks to sim642 - http://www.facepunch.com/showthread.php?t=1239244&p=39204496&viewfull=1#post39204496

#ifndef SSVS_DELEGATE
#define SSVS_DELEGATE

#include <vector>
#include <functional>

namespace ssvs
{
	namespace Utils
	{
		template<typename TReturn, typename... TArgs> class Delegate
		{
			private:
				using Func = std::function<TReturn(TArgs...)>;
				std::vector<Func> funcs;

			public:
				template<typename T> Delegate& operator+=(T mFunc) { funcs.push_back(Func(mFunc)); return *this; }
				std::vector<TReturn> operator()(TArgs... mArgs)
				{
					std::vector<TReturn> result;
					for (auto& f : funcs) result.push_back(f(mArgs...));
					return result;
				}
		};

		template<typename... TArgs> class Delegate<void, TArgs...>
		{
			private:
				using Func = std::function<void(TArgs...)>;
				std::vector<Func> funcs;

			public:
				template<typename T> Delegate& operator+=(T mFunc) { funcs.push_back(Func(mFunc)); return *this; }
				void operator()(TArgs... mArgs) { for (auto& f : funcs) f(mArgs...); }
		};
	}
}

#endif 
