// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_N_USE_JSON
#ifndef SSVS_JSON_UTILSJSON
#define SSVS_JSON_UTILSJSON

#include <SSVUtilsJson/SSVUtilsJson.h>
#include "SSVStart/Tileset/Tileset.h"
#include "SSVStart/Animation/Animation.h"
#include "SSVStart/Input/Combo.h"
#include "SSVStart/Input/Trigger.h"

namespace ssvs
{
	class AssetManager;

	namespace Utils
	{
		Tileset getTilesetFromJson(const Json::Value& mRoot);
		Animation getAnimationFromJson(const Json::Value& mRoot);
		Input::Combo getInputComboFromJson(const Json::Value& mArray);
		Input::Trigger getInputTriggerFromJson(const Json::Value& mArray);
		void loadAssetsFromJson(AssetManager& mAssetManager, const std::string& mRootPath, const Json::Value& mRoot);
	}
}

#endif
#endif
