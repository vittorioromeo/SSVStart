// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO
#define SSVS_INPUT_COMBO

#include <vector>
#include <functional>
#include <SFML/Window.hpp>

namespace ssvs
{
	class GameWindow;

	namespace Input
	{
		class Combo
		{
			private:
				std::vector<sf::Keyboard::Key> keys;
				std::vector<sf::Mouse::Button> buttons;

			public:
				Combo() = default;
				Combo(std::initializer_list<sf::Keyboard::Key> mKeys, std::initializer_list<sf::Mouse::Button> mButtons = {});
				Combo(std::initializer_list<sf::Mouse::Button> mButtons);

				bool isDown(GameWindow& mGameWindow);

				void addKey(sf::Keyboard::Key mKey);
				void addButton(sf::Mouse::Button mButton);
		};
	}
}

#endif
