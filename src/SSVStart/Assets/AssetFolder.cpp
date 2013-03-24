// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Assets/AssetManager.h"
#include "SSVStart/Assets/AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvu;
using namespace ssvu::FileSystem;

namespace ssvs
{
	AssetFolder::AssetFolder(const string& mRootPath) : rootPath{mRootPath}, files{getRecursiveFiles(rootPath)} { }
	void AssetFolder::loadToManager(AssetManager& mAssetManager)
	{
		loadImagesToManager(mAssetManager);
		loadSoundsToManager(mAssetManager);
		loadMusicsToManager(mAssetManager);
		loadFontsToManager(mAssetManager);
	}

	vector<string> AssetFolder::getFilteredFiles(const vector<string>& mExtensions)
	{
		vector<string> result;
		for(auto& file : files) for(auto& extension : mExtensions) if(hasExtension(file, extension)) result.push_back(file);
		return result;
	}
	void AssetFolder::loadFontsToManager(AssetManager& mAssetManager)
	{
		for(auto& file : getFilteredFiles({".ttf", ".otf", ".pfm"}))
		{
			string id{getReplaced(file, rootPath, "")};
			mAssetManager.loadFont(id, file);
			log(id + " font added", "loadFontsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadImagesToManager(AssetManager& mAssetManager)
	{
		for(auto& file : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(file, rootPath, "")};
			mAssetManager.loadImage(id, file);
			log(id + " image added", "loadImagesToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadSoundsToManager(AssetManager& mAssetManager)
	{
		for(auto& file : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(file, rootPath, "")};
			mAssetManager.loadSound(id, file);
			log(id + " soundBuffer added", "loadSoundsToManager(" + rootPath + ")");
			log(id + " sound added", "loadSoundsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadMusicsToManager(AssetManager& mAssetManager)
	{
		for(auto& file : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(file, rootPath, "")};
			mAssetManager.loadMusic(id, file);
			log(id + " music added", "loadMusicsToManager(" + rootPath + ")");
		}
	}
}

