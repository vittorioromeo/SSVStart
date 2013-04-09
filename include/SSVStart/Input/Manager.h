// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

#include <vector>
#include <functional>
#include <SFML/Window.hpp>

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Trigger;

		class Manager
		{
			public:
				typedef std::function<void(float)> InputFunc;
				typedef std::pair<Trigger, InputFunc> InputFuncPair;

			private:
				std::vector<InputFuncPair> pairs;

			public:
				void add(Trigger mInputCombination, InputFunc mInputFunc);
				void update(GameWindow& mGameWindow, float mFrameTime);
				void refresh(GameWindow& mGameWindow);
		};
	}
}

#endif
