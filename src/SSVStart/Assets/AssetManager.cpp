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
	Image& AssetManager::loadImage(const string& mId, const string& mPath)
	{
		log(mId + " image loading", "ssvs::AssetManager::loadImages");
		return images.load(mId, mPath);
	}
	Texture& AssetManager::loadTexture(const string& mId, const string& mPath)
	{
		log(mId + "texture loading", "ssvs::AssetManager::loadTextures");
		return textures.load(mId, mPath);
	}
	Texture& AssetManager::loadTexture(const string& mId, const Image& mImage)
	{
		log(mId + "texture loading", "ssvs::AssetManager::loadTextures");
		return textures.load(mId, mImage);
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
	Shader& AssetManager::loadShader(const string& mId, const string& mPath, Shader::Type mType, Internal::ShaderFromPath)
	{
		log(mId + " shader loading", "ssvs::AssetManager::loadShader");
		return shaders.load(mId, mPath, mType, Internal::ShaderFromPath{});
	}
	Shader& AssetManager::loadShader(const string& mId, const string& mShader, Shader::Type mType, Internal::ShaderFromMemory)
	{
		log(mId + " shader loading", "ssvs::AssetManager::loadShader");
		return shaders.load(mId, mShader, mType, Internal::ShaderFromMemory{});
	}

	bool AssetManager::hasFont(const string& mId)			{ return fonts.has(mId); }
	bool AssetManager::hasImage(const string& mId)			{ return images.has(mId); }
	bool AssetManager::hasTexture(const string& mId)		{ return textures.has(mId); }
	bool AssetManager::hasSoundBuffer(const string& mId)	{ return soundBuffers.has(mId); }
	bool AssetManager::hasSound(const string& mId)			{ return sounds.has(mId); }
	bool AssetManager::hasMusic(const string& mId)			{ return musics.has(mId); }
	bool AssetManager::hasShader(const string& mId)			{ return shaders.has(mId); }

	Font& AssetManager::getFont(const string& mId)					{ assert(hasFont(mId)); return fonts[mId]; }
	Image& AssetManager::getImage(const string& mId)				{ assert(hasImage(mId)); return images[mId]; }
	Texture& AssetManager::getTexture(const string& mId)			{ assert(hasTexture(mId)); return textures[mId]; }
	SoundBuffer& AssetManager::getSoundBuffer(const string& mId)	{ assert(hasSoundBuffer(mId)); return soundBuffers[mId]; }
	Sound& AssetManager::getSound(const string& mId)				{ assert(hasSound(mId)); return sounds[mId]; }
	Music& AssetManager::getMusic(const string& mId)				{ assert(hasMusic(mId)); return musics[mId]; }
	Shader& AssetManager::getShader(const string& mId)				{ assert(hasShader(mId)); return shaders[mId]; }

	unordered_map<string, unique_ptr<Font>>& AssetManager::getFonts()				{ return fonts.getResources(); }
	unordered_map<string, unique_ptr<Image>>& AssetManager::getImages()				{ return images.getResources(); }
	unordered_map<string, unique_ptr<Texture>>& AssetManager::getTextures()			{ return textures.getResources(); }
	unordered_map<string, unique_ptr<SoundBuffer>>& AssetManager::getSoundBuffers()	{ return soundBuffers.getResources(); }
	unordered_map<string, unique_ptr<Sound>>& AssetManager::getSounds()				{ return sounds.getResources(); }
	unordered_map<string, unique_ptr<Music>>& AssetManager::getMusics()				{ return musics.getResources(); }
	unordered_map<string, unique_ptr<Shader>>& AssetManager::getShaders()			{ return shaders.getResources(); }

	void AssetManager::stopSounds() { for(const auto& p : getSounds()) p.second->stop(); }
	void AssetManager::stopMusics() { for(const auto& p : getMusics()) p.second->stop(); }
}

