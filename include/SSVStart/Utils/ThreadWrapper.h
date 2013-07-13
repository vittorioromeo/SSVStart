// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_THREADWRAPPER
#define SSVS_UTILS_THREADWRAPPER

#include <functional>
#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>

namespace ssvs
{
	namespace Utils
	{
		class ThreadWrapper : public ssvu::MemoryManageable
		{
			private:
				bool launched{false}, finished{false};
				std::function<void()> func;
				sf::Thread thread;

			public:
				ThreadWrapper(std::function<void()> mFunction) : func{[&, mFunction]{ mFunction(); finished = true; }}, thread{func} { }

				inline void launch()		{ thread.launch(); launched = true; }
				inline void terminate()		{ thread.terminate(); finished = true; }

				inline bool getLaunched()	{ return launched; }
				inline bool getFinished()	{ return finished; }
		};
	}
}

#endif
