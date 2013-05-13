// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Json/UtilsJson.h"
#include "SSVStart/Utils/UtilsInput.h"

using namespace std;
using namespace sf;
using namespace ssvu;
using namespace ssvuj;
using namespace ssvs::Utils;

namespace ssvs
{
	namespace Utils
	{
		Tileset getTilesetFromJSON(const Json::Value mRoot)
		{
			Vector2i tileSize{as<int>(mRoot, "tileWidth"), as<int>(mRoot, "tileHeight")};
			Tileset result{tileSize};

			Json::Value labels{mRoot["labels"]};
			for(unsigned int iY{0}; iY < labels.size(); ++iY)
				for(unsigned int iX{0}; iX < labels[iY].size(); ++iX)
					result.setLabel(labels[iY][iX].asString(), iX, iY);

			return result;
		}

		ssvs::Animation getAnimationFromJSON(const Json::Value mRoot)
		{
			ssvs::Animation result;

			for(const auto& frame : mRoot["frames"]) result.addStep({as<string>(frame, 0), as<float>(frame, 1)});

			result.setLoop(as<bool>(mRoot, "loop", true));
			result.setPingPong(as<bool>(mRoot, "pingPong", false));
			result.setReverse(as<bool>(mRoot, "reverse", false));
			result.setSpeed(as<float>(mRoot, "speed", 1.f));

			return result;
		}

		Input::Combo getInputComboFromJSON(const Json::Value mArray)
		{
			Input::Combo result;

			for(const auto& inputName : as<vector<string>>(mArray))
			{
				if(isKeyNameValid(inputName)) result.addKey(getKey(inputName));
				else if(isButtonNameValid(inputName)) result.addButton(getButton(inputName));
				else log("<" + inputName + "> is not a valid input name", "getInputComboFromJSON");
			}

			return result;
		}
		Input::Trigger getInputTriggerFromJSON(const Json::Value mArray)
		{
			Input::Trigger result;

			for(const auto& comboArray : as<vector<Json::Value>>(mArray))
				result.add(getInputComboFromJSON(comboArray));

			return result;
		}
	}
}
