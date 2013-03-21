// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETREPOSITORY
#define SSVS_ASSETREPOSITORY

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace ssvs
{
	class AssetManager
	{
		private:
			std::map<std::string, sf::Font*> fonts; // owned
			std::map<std::string, sf::Image*> images; // owned
			std::map<std::string, sf::Texture*> textures; // owned
			std::map<std::string, sf::SoundBuffer*> soundBuffers; // owned
			std::map<std::string, sf::Sound*> sounds; // owned
			std::map<std::string, sf::Music*> musics; // owned

		public:
			AssetManager() = default;
			~AssetManager();

			void loadFolder(const std::string& mPath);
			void loadFont(const std::string& mId, const std::string& mPath);
			void loadImage(const std::string& mId, const std::string& mPath);
			void loadSound(const std::string& mId, const std::string& mPath);
			void loadMusic(const std::string& mId, const std::string& mPath);

			sf::Font& getFont(const std::string& mId);
			sf::Texture& getTexture(const std::string& mId);
			sf::Sound& getSound(const std::string& mId);
			sf::Music& getMusic(const std::string& mId);

			std::map<std::string, sf::Font*>& getFonts();
			std::map<std::string, sf::Image*>& getImages();
			std::map<std::string, sf::Texture*>& getTextures();
			std::map<std::string, sf::SoundBuffer*>& getSoundBuffers();
			std::map<std::string, sf::Sound*>& getSounds();
			std::map<std::string, sf::Music*>& getMusics();

			void stopSounds();
	};
}

#endif
