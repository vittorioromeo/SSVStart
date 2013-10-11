// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_INPUT_COMBO
#define SSVS_INPUT_COMBO

#include <bitset>
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
				std::bitset<sf::Keyboard::Key::KeyCount> keys;
				std::bitset<sf::Mouse::Button::ButtonCount> buttons;

			public:
				Combo() = default;
				Combo(const std::initializer_list<sf::Keyboard::Key>& mKeys, const std::initializer_list<sf::Mouse::Button>& mButtons = {})
				{
					for(const auto& k : mKeys) addKey(k);
					for(const auto& b : mButtons) addButton(b);
				}
				Combo(const std::initializer_list<sf::Mouse::Button>& mButtons) : Combo{{}, mButtons} { }

				bool isDown(GameWindow& mGameWindow) const;

				inline void addKey(sf::Keyboard::Key mKey)			{ keys[mKey] = true; }
				inline void addButton(sf::Mouse::Button mButton)	{ buttons[mButton] = true; }

				inline const decltype(keys)& getKeys() const noexcept		{ return keys; }
				inline const decltype(buttons)& getButtons() const noexcept	{ return buttons; }
		};
	}
}

#endif
