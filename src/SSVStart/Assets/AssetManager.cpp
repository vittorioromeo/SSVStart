// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Assets/AssetManager.h"
#include "SSVStart/Assets/AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvu;

namespace ssvs
{
	AssetManager::~AssetManager()
	{
		for(const auto& pair : images) delete pair.second;
		for(const auto& pair : textures) delete pair.second;
		for(const auto& pair : soundBuffers) delete pair.second;
		for(const auto& pair : sounds) delete pair.second;
		for(const auto& pair : musics) delete pair.second;
	}

	void AssetManager::loadFolder(const std::string& mPath) { AssetFolder folder{mPath}; folder.loadToManager(*this); }
	Font& AssetManager::loadFont(const string& mId, const string& mPath)
	{
		Font* font{new Font}; font->loadFromFile(mPath); fonts[mId] = font;
		log(mId + " font added", "loadFonts");
		return *font;
	}
	Texture& AssetManager::loadImage(const string& mId, const string& mPath)
	{
		Image* image{new Image}; image->loadFromFile(mPath); images[mId] = image;
		log(mId + " image added", "loadImages");
		Texture* texture{new Texture}; texture->loadFromImage(*image); textures[mId] = texture;
		log(mId + " texture added", "loadImages");
		return *texture;
	}
	Sound& AssetManager::loadSound(const string& mId, const string& mPath)
	{
		SoundBuffer* soundBuffer{new SoundBuffer}; soundBuffer->loadFromFile(mPath); soundBuffers[mId] = soundBuffer;
		log(mId + " soundBuffer added", "loadSound");
		Sound* sound{new Sound{*soundBuffer}}; sounds[mId] = sound;
		log(mId + " sound added", "loadSound");
		return *sound;
	}
	Music& AssetManager::loadMusic(const string& mId, const string& mPath)
	{
		Music* music{new Music}; music->openFromFile(mPath); musics[mId] = music;
		log(mId + " music added", "loadMusic");
		return *music;
	}

	bool AssetManager::hasFont(const string& mId)		{ return fonts.count(mId) > 0; }
	bool AssetManager::hasTexture(const string& mId)	{ return textures.count(mId) > 0; }
	bool AssetManager::hasSound(const string& mId)		{ return sounds.count(mId) > 0; }
	bool AssetManager::hasMusic(const string& mId)		{ return musics.count(mId) > 0; }

	Font& AssetManager::getFont(const string& mId)
	{
		#ifndef SSVS_DISABLE_ASSET_CHECKING
			if(fonts.count(mId) == 0) log(mId + " font doesn't exist", "getFont");
		#endif

		return *fonts[mId];
	}
	Texture& AssetManager::getTexture(const string& mId)
	{
		#ifndef SSVS_DISABLE_ASSET_CHECKING
			if(textures.count(mId) == 0) log(mId + " texture doesn't exist", "getTexture");
		#endif

		return *textures[mId];
	}
	Sound& AssetManager::getSound(const string& mId)
	{
		#ifndef SSVS_DISABLE_ASSET_CHECKING
			if(sounds.count(mId) == 0) log(mId + " sound doesn't exist", "getSound");
		#endif

		return *sounds[mId];
	}
	Music& AssetManager::getMusic(const string& mId)
	{
		#ifndef SSVS_DISABLE_ASSET_CHECKING
			if(musics.count(mId) == 0) log(mId + " music doesn't exist", "getMusic");
		#endif

		return *musics[mId];
	}

	unordered_map<string, Font*>& AssetManager::getFonts()					{ return fonts; }
	unordered_map<string, Image*>& AssetManager::getImages()				{ return images; }
	unordered_map<string, Texture*>& AssetManager::getTextures()			{ return textures; }
	unordered_map<string, SoundBuffer*>& AssetManager::getSoundBuffers()	{ return soundBuffers; }
	unordered_map<string, Sound*>& AssetManager::getSounds()				{ return sounds; }
	unordered_map<string, Music*>& AssetManager::getMusics()				{ return musics; }

	void AssetManager::stopSounds() { for(const auto& pair : sounds) pair.second->stop(); }
	void AssetManager::stopMusics() { for(const auto& pair : musics) pair.second->stop(); }
}

