// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESTATE
#define SSVS_GAMESTATE

#include <vector>
#include <functional>
#include <SSVUtils.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Input/Manager.h"
#include "Input/Trigger.h"

namespace ssvs
{
	class GameWindow;
	namespace Input { class Trigger; }

	class GameState
	{
		friend class GameWindow;
		
		private:
			typedef Input::Trigger ITrigger;
			typedef Input::Trigger::Types ITypes;
			typedef Input::Manager::InputFunc IFunc;

			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			Input::Manager inputManager;

		public:
			ssvu::Delegate<void> onDraw;
			ssvu::Delegate<void, float> onUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			void update(float mFrameTime);
			void updateInput(float mFrameTime);
			void draw();

			void addInput(ITrigger mTrigger, IFunc mInputFunc, ITypes mType = ITypes::CONTINUOUS);
		};
	}
	
#endif
