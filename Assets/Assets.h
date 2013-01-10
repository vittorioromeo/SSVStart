#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "../Log/Log.h"
#include "../FileSystem/FileSystem.h"

namespace ssvs
{
	namespace Assets
	{
		void init();
		void initImages();
		void initTextures();

		sf::Texture& getTexture(const std::string& mId);
	}
}

#endif // ASSETS_H
