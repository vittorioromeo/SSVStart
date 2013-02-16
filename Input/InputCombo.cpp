#include "InputCombo.h"

using namespace sf;
using namespace std;

namespace ssvs
{
	InputCombo::InputCombo(initializer_list<Keyboard::Key> mKeys, initializer_list<Mouse::Button> mButtons) : keys{mKeys}, buttons{mButtons} { }
	InputCombo::InputCombo(initializer_list<Mouse::Button> mButtons) : InputCombo{{}, mButtons} { }

	bool InputCombo::isDown(GameWindow& mGameWindow)
	{
		for(auto& key : keys) if (!mGameWindow.isKeyPressed(key)) return false;
		for(auto& button : buttons) if (!mGameWindow.isButtonPressed(button)) return false;
		return true;
	}

	void InputCombo::updateRelease(GameWindow& mGameWindow) { released = !isDown(mGameWindow); }

	bool InputCombo::isActive(GameWindow& mGameWindow)
	{
		if(type == ComboType::SINGLE) return released && isDown(mGameWindow);
		else if(type == ComboType::CONTINUOUS) return isDown(mGameWindow);
		return false;
	}
	void InputCombo::setType(ComboType mType) { type = mType; }
	void InputCombo::setReleased(bool mValue) { released = mValue; }
}

