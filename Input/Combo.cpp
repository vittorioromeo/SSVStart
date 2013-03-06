#include "Combo.h"

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
			for(auto& key : keys) if(!mGameWindow.isKeyPressed(key)) return false;
			for(auto& button : buttons) if(!mGameWindow.isButtonPressed(button)) return false;
			return true;
		}
	}
}

