// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <thread>
#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Json/UtilsJson.h"
#include "SSVStart/Utils/UtilsInput.h"
#include "SSVStart/Assets/AssetManager.h"

using namespace std;
using namespace sf;
using namespace ssvu;
using namespace ssvuj;

namespace ssvs
{
	namespace Utils
	{
		Tileset getTilesetFromJson(const ssvuj::Value& mRoot)
		{
			Vec2u tileSize{as<unsigned int>(mRoot, "tileWidth"), as<unsigned int>(mRoot, "tileHeight")};
			Tileset result{tileSize};

			const ssvuj::Value& labels(mRoot["labels"]);
			for(unsigned int iY{0}; iY < size(labels); ++iY)
				for(unsigned int iX{0}; iX < size(labels[iY]); ++iX)
					result.setLabel(as<string>(labels[iY][iX]), {iX, iY});

			return result;
		}

		Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Value& mRoot)
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

		Input::Combo getInputComboFromJson(const ssvuj::Value& mArray)
		{
			Input::Combo result;

			for(const auto& inputName : as<vector<string>>(mArray))
			{
				if(isKeyNameValid(inputName)) result.addKey(getKey(inputName));
				else if(isButtonNameValid(inputName)) result.addButton(getButton(inputName));
				else log("<" + inputName + "> is not a valid input name", "ssvs::Utils::getInputComboFromJSON");
			}

			return result;
		}
		Input::Trigger getInputTriggerFromJson(const ssvuj::Value& mArray)
		{
			Input::Trigger result;

			for(const auto& comboArray : as<vector<ssvuj::Value>>(mArray))
				result.add(getInputComboFromJson(comboArray));

			return result;
		}
		BitmapFontData getBitmapFontDataFromJson(const ssvuj::Value& mRoot)
		{
			unsigned int cellColumns(as<int>(mRoot, "cellColumns"));
			unsigned int cellWidth(as<int>(mRoot, "cellWidth"));
			unsigned int cellHeight(as<int>(mRoot, "cellHeight"));
			unsigned int cellStart(as<int>(mRoot, "cellStart"));

			return {cellColumns, cellWidth, cellHeight, cellStart};
		}

		void loadAssetsFromJson(AssetManager& mAssetManager, const string& mRootPath, const ssvuj::Value& mRoot)
		{
			thread t1{[&]{ for(const auto& f : as<vector<string>>(mRoot, "fonts"))				mAssetManager.loadFont(f, mRootPath + f); }};
			thread t2{[&]{ for(const auto& f : as<vector<string>>(mRoot, "images"))				mAssetManager.loadImage(f, mRootPath + f); }};
			thread t3{[&]{ for(const auto& f : as<vector<string>>(mRoot, "textures"))			mAssetManager.loadTexture(f, mRootPath + f); }};
			thread t4{[&]{ for(const auto& f : as<vector<string>>(mRoot, "soundBuffers"))		mAssetManager.loadSoundBuffer(f, mRootPath + f); }};
			thread t5{[&]{ for(const auto& f : as<vector<string>>(mRoot, "musics"))				mAssetManager.loadMusic(f, mRootPath + f); }};
			thread t6{[&]{ for(const auto& f : as<vector<string>>(mRoot, "shadersVertex"))		mAssetManager.loadShader(f, mRootPath + f, Shader::Type::Vertex, Internal::ShaderFromPath{}); }};
			thread t7{[&]{ for(const auto& f : as<vector<string>>(mRoot, "shadersFragment"))	mAssetManager.loadShader(f, mRootPath + f, Shader::Type::Fragment, Internal::ShaderFromPath{}); }};
			t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join();
		}
	}
}
