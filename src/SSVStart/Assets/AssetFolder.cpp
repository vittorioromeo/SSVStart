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
	AssetFolder::AssetFolder(const Path& mRootPath) : rootPath{mRootPath}, files{getScan<Mode::Recurse, Type::File>(rootPath)} { }
	void AssetFolder::loadToManager(AssetManager& mAssetManager)
	{
		loadImagesToManager(mAssetManager);
		loadTexturesToManager(mAssetManager);
		loadSoundBuffersToManager(mAssetManager);
		loadMusicsToManager(mAssetManager);
		loadFontsToManager(mAssetManager);
		loadShadersToManager(mAssetManager);
	}

	vector<Path> AssetFolder::getFilteredFiles(const vector<string>& mExtensions)
	{
		vector<Path> result;
		for(const auto& f : files) for(const auto& e : mExtensions) if(f.hasExtension(e)) result.push_back(f);
		return result;
	}
	void AssetFolder::loadFontsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".ttf", ".otf", ".pfm"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Font>(id, f);
			lo << lt("ssvs::AssetFolder::loadFontsToManager(" + rootPath.getStr() + ")") << id + " font added" << endl;
		}
	}
	void AssetFolder::loadImagesToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Image>(id, f);
			lo << lt("ssvs::AssetFolder::loadImagesToManager(" + rootPath.getStr() + ")") << id + " image added" << endl;
		}
	}
	void AssetFolder::loadTexturesToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".png", ".jpg", ".bmp", ".jpeg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Texture>(id, f);
			lo << lt("ssvs::AssetFolder::loadTexturesToManager(" + rootPath.getStr() + ")") << id + " texture added" << endl;
		}
	}
	void AssetFolder::loadSoundBuffersToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<SoundBuffer>(id, f);
			lo << lt("ssvs::AssetFolder::loadSoundsToManager(" + rootPath.getStr() + ")") << id + " soundBuffer added" << endl;
		}
	}
	void AssetFolder::loadMusicsToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".wav", ".ogg"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Music>(id, f);
			lo << lt("ssvs::AssetFolder::loadMusicsToManager(" + rootPath.getStr() + ")") << id + " music added" << endl;
		}
	}
	void AssetFolder::loadShadersToManager(AssetManager& mAssetManager)
	{
		for(const auto& f : getFilteredFiles({".vert"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Shader>(id, f, Shader::Type::Vertex, Internal::ShaderFromPath{});
			lo << lt("ssvs::AssetFolder::loadShadersToManager(" + rootPath.getStr() + ")") << id + " vertex shader added" << endl;
		}
		for(const auto& f : getFilteredFiles({".frag"}))
		{
			string id{getReplaced(f, rootPath, "")};
			mAssetManager.load<Shader>(id, f, Shader::Type::Fragment, Internal::ShaderFromPath{});
			lo << lt("ssvs::AssetFolder::loadShadersToManager(" + rootPath.getStr() + ")") << id + " fragment shader added" << endl;
		}
	}
}

