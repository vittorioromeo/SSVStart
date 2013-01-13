#ifndef INPUTCOMBINATION_H
#define INPUTCOMBINATION_H

#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../GameSystem/GameWindow.h"

namespace ssvs
{
	struct InputCombination
	{
		std::vector<sf::Keyboard::Key> keys;
		std::vector<sf::Mouse::Button> buttons;

		InputCombination(std::initializer_list<sf::Keyboard::Key> mKeys, std::initializer_list<sf::Mouse::Button> mButtons = {});
		InputCombination(std::initializer_list<sf::Mouse::Button> mButtons);

		bool isDown(GameWindow& mGameWindow);
	};
}

#endif // INPUTCOMBINATION_H
