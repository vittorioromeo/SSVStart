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
				Combo(const std::initializer_list<sf::Keyboard::Key>& mKeys, const std::initializer_list<sf::Mouse::Button>& mButtons = {});
				Combo(const std::initializer_list<sf::Mouse::Button>& mButtons);

				bool isDown(GameWindow& mGameWindow) const;

				inline void addKey(sf::Keyboard::Key mKey) { keys.push_back(mKey); }
				inline void addButton(sf::Mouse::Button mButton) { buttons.push_back(mButton); }

				inline const std::vector<sf::Keyboard::Key>& getKeys() const	{ return keys; }
				inline const std::vector<sf::Mouse::Button>& getButtons() const { return buttons; }
		};
	}
}

#endif
