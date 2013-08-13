// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO
#define SSVS_INPUT_COMBO

#include <vector>
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
				Combo(const std::initializer_list<sf::Keyboard::Key>& mKeys, const std::initializer_list<sf::Mouse::Button>& mButtons = {}) : keys{mKeys}, buttons{mButtons} { }
				Combo(const std::initializer_list<sf::Mouse::Button>& mButtons) : Combo{{}, mButtons} { }

				bool isDown(GameWindow& mGameWindow) const;

				inline void addKey(sf::Keyboard::Key mKey)			{ keys.push_back(mKey); }
				inline void addButton(sf::Mouse::Button mButton)	{ buttons.push_back(mButton); }

				inline const decltype(keys)& getKeys() const		{ return keys; }
				inline const decltype(buttons)& getButtons() const	{ return buttons; }
		};
	}
}

#endif
