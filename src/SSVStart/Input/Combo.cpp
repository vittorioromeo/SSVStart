// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/Input/Combo.h"
#include "SSVStart/GameSystem/GameWindow.h"

using namespace sf;
using namespace std;

namespace ssvs
{
	namespace Input
	{
		Combo::Combo(initializer_list<Keyboard::Key> mKeys, initializer_list<Mouse::Button> mButtons) : keys{mKeys}, buttons{mButtons} { }
		Combo::Combo(initializer_list<Mouse::Button> mButtons) : Combo{{}, mButtons} { }

		bool Combo::isDown(GameWindow& mGameWindow)
		{
			if(keys.empty() && buttons.empty()) return false;
			for(auto& key : keys) if(!mGameWindow.isKeyPressed(key)) return false;
			for(auto& button : buttons) if(!mGameWindow.isButtonPressed(button)) return false;
			return true;
		}

		void Combo::addKey(Keyboard::Key mKey) { keys.push_back(mKey); }
		void Combo::addButton(Mouse::Button mButton) { buttons.push_back(mButton); }
	}
}

