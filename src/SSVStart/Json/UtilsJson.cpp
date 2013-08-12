// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <future>
#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Json/UtilsJson.h"
#include "SSVStart/Assets/AssetManager.h"

using namespace std;
using namespace sf;
using namespace ssvu;
using namespace ssvuj;

namespace ssvs
{
	namespace Utils
	{
		Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Obj& mRoot)
		{
			Animation result;

			for(const auto& f : mRoot["frames"])
			{
				const auto& index(mTileset.getIndex(as<string>(f, 0)));
				result.addStep({index, as<float>(f, 1)});
			}

			result.setLoop(as<bool>(mRoot, "loop", true));
			result.setPingPong(as<bool>(mRoot, "pingPong", false));
			result.setReverse(as<bool>(mRoot, "reverse", false));
			result.setSpeed(as<float>(mRoot, "speed", 1.f));

			return result;
		}

		void loadAssetsFromJson(AssetManager& mAssetManager, const Path& mRootPath, const ssvuj::Obj& mRoot)
		{
			auto a1 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "fonts"))				mAssetManager.load<Font>(f, mRootPath + f); });
			auto a2 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "images"))			mAssetManager.load<Image>(f, mRootPath + f); });
			auto a3 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "textures"))			mAssetManager.load<Texture>(f, mRootPath + f); });
			auto a4 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "soundBuffers"))		mAssetManager.load<SoundBuffer>(f, mRootPath + f); });
			auto a5 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "musics"))			mAssetManager.load<Music>(f, mRootPath + f); });
			auto a6 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "shadersVertex"))		mAssetManager.load<Shader>(f, mRootPath + f, Shader::Type::Vertex, Internal::ShaderFromPath{}); });
			auto a7 = async(launch::async, [&]{ for(const auto& f : as<vector<string>>(mRoot, "shadersFragment"))	mAssetManager.load<Shader>(f, mRootPath + f, Shader::Type::Fragment, Internal::ShaderFromPath{}); });
		}
	}
}
