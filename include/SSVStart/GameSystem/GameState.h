// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESTATE
#define SSVS_GAMESTATE

#include <vector>
#include <functional>
#include <map>
#include <SSVUtils/SSVUtils.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/Input/Manager.h"
#include "SSVStart/Input/Trigger.h"

namespace ssvs
{
	class GameWindow;

	class GameState
	{
		friend class GameWindow;

		private:
			using ITrigger = Input::Trigger;
			using ITypes = ITrigger::Types;
			using IFunc = Input::InputFunc;
			using EventDelegate = ssvu::Delegate<void, const sf::Event&>;

			GameWindow* gameWindowPtr{nullptr}; // not owned, just pointed to
			Input::Manager inputManager;
			std::map<sf::Event::EventType, EventDelegate> eventDelegates;

			void handleEvent(const sf::Event& mEvent);

		public:
			ssvu::Delegate<void> onDraw;
			ssvu::Delegate<void, float> onUpdate;
			ssvu::Delegate<void> onPostUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			void update(float mFrameTime);
			void updateInput(float mFrameTime);
			void refreshInput();
			void draw();

			void addInput(ITrigger mTrigger, IFunc mFuncOn, ITypes mType = ITypes::CONTINUOUS);
			void addInput(ITrigger mTrigger, IFunc mFuncOn, IFunc mInputOff, ITypes mType = ITypes::CONTINUOUS);
			EventDelegate& getEventDelegate(sf::Event::EventType mEventType);
		};
	}

#endif
