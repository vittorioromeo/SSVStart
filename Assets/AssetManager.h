#ifndef ASSETREPOSITORY_H
#define ASSETREPOSITORY_H

#include <map>
#include <string>
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
		class AssetManager
		{
			private:
				std::string rootPath;
				std::vector<std::string> files;
				std::map<std::string, sf::Image*> images; // owned
				std::map<std::string, sf::Texture*> textures; // owned
				std::map<std::string, sf::SoundBuffer*> soundBuffers; // owned
				std::map<std::string, sf::Sound*> sounds; // owned
				std::map<std::string, sf::Music*> musics; // owned

				AssetManager(const AssetManager&) = delete; // non construction-copyable
				AssetManager& operator=(const AssetManager&) = delete; // non copyable

				// Init
				void initImages();
				void initTextures();
				void initSounds();
				void initMusics();

				// Uninit
				void uninitImages();
				void uninitTextures();
				void uninitSounds();
				void uninitMusics();

			public:
				AssetManager(const std::string& mRootPath);
				~AssetManager();				

				// Getters
				sf::Texture& getTexture(const std::string& mId);
				sf::Sound& getSound(const std::string& mId);
				sf::Music& getMusic(const std::string& mId);
		};
	}
}

#endif // ASSETREPOSITORY_H
