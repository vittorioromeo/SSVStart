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
	class InputCombo
	{
		public:
			enum class ComboType{CONTINUOUS, SINGLE};

		private:
			ComboType type{ComboType::CONTINUOUS};
			std::vector<sf::Keyboard::Key> keys;
			std::vector<sf::Mouse::Button> buttons;
			bool released{true};

			bool isDown(GameWindow& mGameWindow);

		public:
			InputCombo(std::initializer_list<sf::Keyboard::Key> mKeys, std::initializer_list<sf::Mouse::Button> mButtons = {});
			InputCombo(std::initializer_list<sf::Mouse::Button> mButtons);

			bool isActive(GameWindow& mGameWindow);
			void updateRelease(GameWindow& mGameWindow);
			void setType(ComboType mType);
			void setReleased(bool mValue);
	};
}

#endif // INPUTCOMBINATION_H
