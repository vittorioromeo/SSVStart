// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_INPUT
#define SSVS_UTILS_INPUT

#include <SFML/Window.hpp>
#include "SSVStart/Input/Combo.h"

namespace ssvs
{
	namespace Utils
	{
		sf::Keyboard::Key getKey(const std::string& mName);
		sf::Mouse::Button getButton(const std::string& mName);
		std::string getKeyName(sf::Keyboard::Key mKey);
		std::string getButtonName(sf::Mouse::Button mButton);
		bool isKeyNameValid(const std::string& mName);
		bool isButtonNameValid(const std::string& mName);
	}
}

#endif
