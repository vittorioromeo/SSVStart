// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Input/InputManager.h"
#include "../Utils/Delegate.h"

namespace ssvs
{
	class GameWindow;
	
	class GameState
	{
		typedef std::function<void()> DrawFunc;
		typedef std::function<void(float)> UpdateFunc;
		typedef std::pair<int, DrawFunc> DrawFuncPair;
		friend class GameWindow;

		private:
			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			InputManager inputManager;

		public:
			Delegate<void> onDraw;
			Delegate<void, float> onUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			void update(float mFrameTime);
			void draw();

			void addInput(InputCombination mInputCombination, InputManager::InputFunc mInputFunc);			
		};
	} /* namespace ssvs */
#endif /* GAME_H_ */
