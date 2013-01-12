#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "../Log/Log.h"
#include "../FileSystem/FileSystem.h"
#include "AssetFolder.h"
#include "AssetManager.h"

namespace ssvs
{
	namespace Assets
	{
		// Init (prevents global initialization freeze of SFML audio objects)
		void init();

		// Getters
		sf::Texture& getTexture(const std::string& mId);
		sf::Sound& getSound(const std::string& mId);
		sf::Music& getMusic(const std::string& mId);
	}
}

#endif // ASSETS_H
