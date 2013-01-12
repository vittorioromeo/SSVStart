#include "InputCombination.h"

using namespace sf;
using namespace std;

namespace ssvs
{
	InputCombination::InputCombination(initializer_list<Keyboard::Key> mKeys,initializer_list<Mouse::Button> mButtons) : keys{mKeys}, buttons{mButtons} { }
	InputCombination::InputCombination(initializer_list<Mouse::Button> mButtons) : InputCombination{{}, mButtons} { }

	bool InputCombination::isDown(GameWindow& mGameWindow)
	{
		for (auto& key : keys) if (!mGameWindow.isKeyPressed(key)) return false;
		for (auto& button : buttons) if (!mGameWindow.isButtonPressed(button)) return false;		
		return true;
	}
}

