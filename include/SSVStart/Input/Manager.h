// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_MANAGER
#define SSVS_INPUT_MANAGER

#include <vector>
#include <functional>
#include "SSVStart/Input/Bind.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Manager
		{
			private:

				std::vector<Bind> binds;

			public:
				inline void update(GameWindow& mGameWindow, float mFT)
				{

					for(auto& b : binds) b.update(mFT, mGameWindow);
				}
				inline void refresh(GameWindow& mGameWindow)						{ for(auto& b : binds) b.refresh(mGameWindow); }
				inline void push(const Bind& mBind)									{ binds.push_back(mBind); }
				template<typename... TArgs> inline void emplace(TArgs&&... mArgs)	{ binds.emplace_back(std::forward<TArgs>(mArgs)...); }
		};
	}
}

#endif
