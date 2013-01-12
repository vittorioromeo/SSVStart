#include "AssetFolder.h"

using namespace std;
using namespace sf;
using namespace ssvs::FileSystem;
using namespace ssvs::Utils;

namespace ssvs
{
	AssetFolder::AssetFolder(const string& mRootPath) : rootPath{mRootPath}, files{getRecursiveFiles(rootPath)} { }
	void AssetFolder::fillManager(AssetManager& mAssetManager)
	{
		initImages(mAssetManager);
		initSounds(mAssetManager);
		initMusics(mAssetManager);
	}

	vector<string> AssetFolder::getFilteredFiles(const vector<string> mExtensions)
	{
		vector<string> result;
		for(auto file : files) for(auto extension : mExtensions) if(hasExtension(file, extension)) result.push_back(file);
		return result;
	}

	void AssetFolder::initImages(AssetManager& mAssetManager)
	{
		static vector<string> extensions{".png", ".jpg", ".bmp", ".jpeg"};
		for(auto file : getFilteredFiles(extensions))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadImage(id, file);
			log(id + " image added", "initImages(" + rootPath + ")");
		}
	}
	void AssetFolder::initSounds(AssetManager& mAssetManager)
	{
		static vector<string> extensions{".wav", ".ogg"};
		for(auto file : getFilteredFiles(extensions))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadSound(id, file);
			log(id + " soundBuffer added", "initSounds(" + rootPath + ")");
			log(id + " sound added", "initSounds(" + rootPath + ")");
		}
	}
	void AssetFolder::initMusics(AssetManager& mAssetManager)
	{
		static vector<string> extensions{".wav", ".ogg"};
		for(auto file : getFilteredFiles(extensions))
		{
			string id{replace(file, rootPath, "")};
			mAssetManager.loadMusic(id, file);
			log(id + " music added", "initMusics(" + rootPath + ")");
		}
	}
}

