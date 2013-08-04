// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMESTATE
#define SSVS_GAMESYSTEM_GAMESTATE

#include <map>
#include <SSVUtils/SSVUtils.h>
#include <SFML/Window.hpp>
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
			using IType = ITrigger::Type;
			using IFunc = Input::InputFunc;
			using EventDelegate = ssvu::Delegate<void(const sf::Event&)>;

			GameWindow* gameWindow{nullptr}; // not owned, just pointed to
			Input::Manager inputManager;
			std::map<sf::Event::EventType, EventDelegate> eventDelegates;

			inline void handleEvent(const sf::Event& mEvent)	{ eventDelegates[mEvent.type](mEvent); }
			inline void update(float mFrameTime)				{ onUpdate(mFrameTime); }
			inline void draw()									{ onDraw(); }
			inline void updateInput(float mFrameTime)			{ inputManager.update(*gameWindow, mFrameTime); }
			inline void refreshInput()							{ inputManager.refresh(*gameWindow); }

		public:
			ssvu::Delegate<void()> onDraw;
			ssvu::Delegate<void(float)> onUpdate;
			ssvu::Delegate<void()> onPostUpdate;

			GameState() = default;
			GameState(const GameState&) = delete; // non construction-copyable
			GameState& operator=(const GameState&) = delete; // non copyable

			inline void addInput(ITrigger mTrigger, IFunc mFuncOn, IType mType = IType::Continuous)					{ mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn}); }
			inline void addInput(ITrigger mTrigger, IFunc mFuncOn, IFunc mFuncOff, IType mType = IType::Continuous)	{ mTrigger.setType(mType); inputManager.add({mTrigger, mFuncOn, mFuncOff}); }

			inline EventDelegate& getEventDelegate(sf::Event::EventType mEventType) { return eventDelegates[mEventType]; }
		};
	}

#endif
