// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace ssvs
{
	class AssetManager
	{
		private:
			std::unordered_map<std::string, sf::Font*> fonts; // owned
			std::unordered_map<std::string, sf::Image*> images; // owned
			std::unordered_map<std::string, sf::Texture*> textures; // owned
			std::unordered_map<std::string, sf::SoundBuffer*> soundBuffers; // owned
			std::unordered_map<std::string, sf::Sound*> sounds; // owned
			std::unordered_map<std::string, sf::Music*> musics; // owned

		public:
			AssetManager() = default;
			~AssetManager();

			void loadFolder(const std::string& mPath);
			sf::Font& loadFont(const std::string& mId, const std::string& mPath);
			sf::Texture& loadImage(const std::string& mId, const std::string& mPath);
			sf::Sound& loadSound(const std::string& mId, const std::string& mPath);
			sf::Music& loadMusic(const std::string& mId, const std::string& mPath);

			bool hasFont(const std::string& mId);
			bool hasTexture(const std::string& mId);
			bool hasSound(const std::string& mId);
			bool hasMusic(const std::string& mId);

			sf::Font& getFont(const std::string& mId);
			sf::Texture& getTexture(const std::string& mId);
			sf::Sound& getSound(const std::string& mId);
			sf::Music& getMusic(const std::string& mId);

			std::unordered_map<std::string, sf::Font*>& getFonts();
			std::unordered_map<std::string, sf::Image*>& getImages();
			std::unordered_map<std::string, sf::Texture*>& getTextures();
			std::unordered_map<std::string, sf::SoundBuffer*>& getSoundBuffers();
			std::unordered_map<std::string, sf::Sound*>& getSounds();
			std::unordered_map<std::string, sf::Music*>& getMusics();

			void stopSounds();
			void stopMusics();
	};
}

#endif
