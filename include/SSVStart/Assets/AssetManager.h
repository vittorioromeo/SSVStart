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
	class Shader;
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
			Internal::ResourceHolder<sf::Shader> shaders;

		public:
			AssetManager() = default;

			void loadFolder(const std::string& mPath);
			sf::Font& loadFont(const std::string& mId, const std::string& mPath);
			sf::Image& loadImage(const std::string& mId, const std::string& mPath);
			sf::Texture& loadTexture(const std::string& mId, const std::string& mPath);
			sf::Texture& loadTexture(const std::string& mId, const sf::Image& mImage);
			sf::Sound& loadSound(const std::string& mId, const std::string& mPath);
			sf::Music& loadMusic(const std::string& mId, const std::string& mPath);
			sf::Shader& loadShader(const std::string& mId, const std::string& mPath, sf::Shader::Type mType, Internal::ShaderFromPath);
			sf::Shader& loadShader(const std::string& mId, const std::string& mShader, sf::Shader::Type mType, Internal::ShaderFromMemory);

			bool hasFont(const std::string& mId);
			bool hasImage(const std::string& mId);
			bool hasTexture(const std::string& mId);
			bool hasSoundBuffer(const std::string& mId);
			bool hasSound(const std::string& mId);
			bool hasMusic(const std::string& mId);
			bool hasShader(const std::string& mId);

			sf::Font& getFont(const std::string& mId);
			sf::Image& getImage(const std::string& mId);
			sf::Texture& getTexture(const std::string& mId);
			sf::SoundBuffer& getSoundBuffer(const std::string& mId);
			sf::Sound& getSound(const std::string& mId);
			sf::Music& getMusic(const std::string& mId);
			sf::Shader& getShader(const std::string& mId);

			std::unordered_map<std::string, std::unique_ptr<sf::Font>>& getFonts();
			std::unordered_map<std::string, std::unique_ptr<sf::Image>>& getImages();
			std::unordered_map<std::string, std::unique_ptr<sf::Texture>>& getTextures();
			std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>>& getSoundBuffers();
			std::unordered_map<std::string, std::unique_ptr<sf::Sound>>& getSounds();
			std::unordered_map<std::string, std::unique_ptr<sf::Music>>& getMusics();
			std::unordered_map<std::string, std::unique_ptr<sf::Shader>>& getShaders();

			void stopSounds();
			void stopMusics();
	};
}

#endif
