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
	AssetFolder::AssetFolder(const string& mRootPath) : rootPath{mRootPath}, files{getScan<Mode::Recurse, Type::File>(rootPath)} { }
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
		for(const auto& f : files) for(const auto& e : mExtensions) if(hasExtension(f, e)) result.push_back(f);
		return result;
	}
	void AssetFolder::loadFontsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".ttf", ".otf", ".pfm"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadFont(id, f);
			log(id + " font added", "ssvs::AssetFolder::loadFontsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadImagesToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadImage(id, f);
			log(id + " image added", "ssvs::AssetFolder::loadImagesToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadSoundsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadSound(id, f);
			log(id + " soundBuffer added", "ssvs::AssetFolder::loadSoundsToManager(" + rootPath + ")");
			log(id + " sound added", "ssvs::AssetFolder::loadSoundsToManager(" + rootPath + ")");
		}
	}
	void AssetFolder::loadMusicsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.loadMusic(id, f);
			log(id + " music added", "ssvs::AssetFolder::loadMusicsToManager(" + rootPath + ")");
		}
	}
}

