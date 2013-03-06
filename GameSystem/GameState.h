// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESTATE
#define SSVS_GAMESTATE

#include <vector>
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Input/Manager.h"
#include "Input/Trigger.h"
#include "Utils/Delegate.h"

namespace ssvs
{
	class GameWindow;
	namespace Input { class Trigger; }

	class GameState
	{
		typedef std::function<void()> DrawFunc;
		typedef std::function<void(float)> UpdateFunc;
		typedef std::pair<int, DrawFunc> DrawFuncPair;
		friend class GameWindow;

		private:
			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			Input::Manager inputManager;

		public:
			Utils::Delegate<void> onDraw;
			Utils::Delegate<void, float> onUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			void update(float mFrameTime);
			void draw();

			void addInput(Input::Trigger mTrigger, Input::Manager::InputFunc mInputFunc, Input::Trigger::Types mType = Input::Trigger::Types::CONTINUOUS);
		};
	}
	
#endif
