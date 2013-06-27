// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

#include <cassert>
#include <string>
#include <memory>
#include <unordered_map>
#include "SSVStart/Assets/Internal/ResourceHolder.h"

namespace sf
{
	class Font;
	class Image;
	class Texture;
	class SoundBuffer;
	class Sound;
	class Music;
}

namespace ssvs
{
	class AssetManager
	{
		private:
			Internal::ResourceHolder<sf::Font> fonts;
			Internal::ResourceHolder<sf::Image> images;
			Internal::ResourceHolder<sf::Texture> textures;
			Internal::ResourceHolder<sf::SoundBuffer> soundBuffers;
			Internal::ResourceHolder<sf::Sound> sounds;
			Internal::ResourceHolder<sf::Music> musics;

		public:
			AssetManager() = default;

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

			std::unordered_map<std::string, std::unique_ptr<sf::Font>>& getFonts();
			std::unordered_map<std::string, std::unique_ptr<sf::Image>>& getImages();
			std::unordered_map<std::string, std::unique_ptr<sf::Texture>>& getTextures();
			std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>& getSoundBuffers();
			std::unordered_map<std::string, std::unique_ptr<sf::Sound>>& getSounds();
			std::unordered_map<std::string, std::unique_ptr<sf::Music>>& getMusics();

			void stopSounds();
			void stopMusics();
	};
}

#endif
