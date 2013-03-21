// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_THREADWRAPPER
#define SSVS_UTILS_THREADWRAPPER

#include <functional>
#include <SFML/System.hpp>

namespace ssvs
{
	namespace Utils
	{
		class ThreadWrapper
		{
			private:
				bool finished{false};
				std::function<void()> func;
				sf::Thread thread;

			public:
				ThreadWrapper(std::function<void()> mFunction) : func{[&, mFunction]{ mFunction(); finished = true; }}, thread{func} { }
				void launch() { thread.launch(); }
				void terminate() { thread.terminate(); }
				bool getFinished() { return finished; }
		};
	}
}

#endif
