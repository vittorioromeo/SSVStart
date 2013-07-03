// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

#include <vector>
#include <functional>
#include "SSVStart/Input/Bind.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		typedef std::function<void(float)> InputFunc;

		class Manager
		{
			private:
				std::vector<Bind> binds;

			public:
				void add(const Bind& mBind);
				void update(GameWindow& mGameWindow, float mFrameTime);
				void refresh(GameWindow& mGameWindow);
		};
	}
}

#endif
