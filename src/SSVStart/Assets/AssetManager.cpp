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
	void AssetManager::loadFolder(const std::string& mPath) { AssetFolder folder{mPath}; folder.loadToManager(*this); }
	Font& AssetManager::loadFont(const string& mId, const string& mPath)
	{
		log(mId + " font loading", "ssvs::AssetManager::loadFonts");
		return fonts.load(mId, mPath);
	}
	Texture& AssetManager::loadImage(const string& mId, const string& mPath)
	{
		log(mId + " image and texture loading", "ssvs::AssetManager::loadImages");
		return textures.load(mId, images.load(mId, mPath));
	}
	Sound& AssetManager::loadSound(const string& mId, const string& mPath)
	{
		log(mId + " soundBuffer and sound loading", "ssvs::AssetManager::loadSound");
		return sounds.load(mId, soundBuffers.load(mId, mPath));
	}
	Music& AssetManager::loadMusic(const string& mId, const string& mPath)
	{
		log(mId + " music loading", "ssvs::AssetManager::loadMusic");
		return musics.load(mId, mPath);
	}

	bool AssetManager::hasFont(const string& mId)		{ return fonts.has(mId); }
	bool AssetManager::hasTexture(const string& mId)	{ return textures.has(mId); }
	bool AssetManager::hasSound(const string& mId)		{ return sounds.has(mId); }
	bool AssetManager::hasMusic(const string& mId)		{ return musics.has(mId); }

	Font& AssetManager::getFont(const string& mId)			{ assert(hasFont(mId)); return fonts[mId]; }
	Texture& AssetManager::getTexture(const string& mId)	{ assert(hasTexture(mId)); return textures[mId]; }
	Sound& AssetManager::getSound(const string& mId)		{ assert(hasSound(mId)); return sounds[mId]; }
	Music& AssetManager::getMusic(const string& mId)		{ assert(hasMusic(mId)); return musics[mId]; }

	unordered_map<string, unique_ptr<Font>>& AssetManager::getFonts()				{ return fonts.getResources(); }
	unordered_map<string, unique_ptr<Image>>& AssetManager::getImages()				{ return images.getResources(); }
	unordered_map<string, unique_ptr<Texture>>& AssetManager::getTextures()			{ return textures.getResources(); }
	unordered_map<string, unique_ptr<SoundBuffer>>& AssetManager::getSoundBuffers()	{ return soundBuffers.getResources(); }
	unordered_map<string, unique_ptr<Sound>>& AssetManager::getSounds()				{ return sounds.getResources(); }
	unordered_map<string, unique_ptr<Music>>& AssetManager::getMusics()				{ return musics.getResources(); }

	void AssetManager::stopSounds() { for(const auto& p : getSounds()) p.second->stop(); }
	void AssetManager::stopMusics() { for(const auto& p : getMusics()) p.second->stop(); }
}

