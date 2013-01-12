#include "AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;
using namespace ssvs::Utils;

namespace ssvs
{
	AssetFolder::AssetFolder(const string& mRootPath) : rootPath{mRootPath}, files{getRecursiveFiles(rootPath)} { }
	void AssetFolder::loadToManager(AssetManager& mAssetManager) { loadImagesToManager(mAssetManager); loadSoundsToManager(mAssetManager); loadMusicsToManager(mAssetManager); }

	vector<string> AssetFolder::getFilteredFiles(const vector<string> mExtensions)
	{
		vector<string> result;
		for(auto file : files) for(auto extension : mExtensions) if(hasExtension(file, extension)) result.push_back(file);
		return result;
	}
	void AssetFolder::loadImagesToManager(AssetManager& mAssetManager)
	{
		for(auto file : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadImage(id, file);
			log(id + " image added", "initImages(" + rootPath + ")");
		}
	}
	void AssetFolder::loadSoundsToManager(AssetManager& mAssetManager)
	{
		for(auto file : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadSound(id, file);
			log(id + " soundBuffer added", "initSounds(" + rootPath + ")");
			log(id + " sound added", "initSounds(" + rootPath + ")");
		}
	}
	void AssetFolder::loadMusicsToManager(AssetManager& mAssetManager)
	{
		for(auto file : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadMusic(id, file);
			log(id + " music added", "initMusics(" + rootPath + ")");
		}
	}
}

