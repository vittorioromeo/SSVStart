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
#include "SSVStart/BitmapFont/BitmapFont.h"
#include "SSVStart/Utils/UtilsInput.h"
#include "SSVStart/Global/Typedefs.h"

namespace ssvuj
{
	namespace Internal
	{
		template<> struct Converter<ssvs::Input::Combo>
		{
			using T = ssvs::Input::Combo;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				for(const auto& inputName : as<std::vector<std::string>>(mObj))
				{
					if(ssvs::Utils::isKeyNameValid(inputName)) mValue.addKey(ssvs::Utils::getKey(inputName));
					else if(ssvs::Utils::isButtonNameValid(inputName)) mValue.addButton(ssvs::Utils::getButton(inputName));
					else ssvu::lo << ssvu::lt("ssvs::Utils::getInputComboFromJSON") << "<" << inputName << "> is not a valid input name";
				}
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				auto i(0u);
				const auto& keys(mValue.getKeys());
				const auto& buttons(mValue.getButtons());
				for(auto j(0u); j < keys.size(); ++i, ++j) set(mObj, i, ssvs::Utils::getKeyName(keys[j]));
				for(auto j(0u); j < buttons.size(); ++i, ++j) set(mObj, i, ssvs::Utils::getButtonName(buttons[j]));
			}
		};
		template<> struct Converter<ssvs::Input::Trigger>
		{
			using T = ssvs::Input::Trigger;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				for(const auto& comboArray : as<std::vector<Obj>>(mObj)) mValue.add(as<ssvs::Input::Combo>(comboArray));
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				const auto& combos(mValue.getCombos());
				for(auto i(0u); i < combos.size(); ++i) set(mObj, i, combos[i]);
			}
		};
		template<> struct Converter<ssvs::Tileset>
		{
			using T = ssvs::Tileset;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				ssvs::Vec2u tileSize{as<unsigned int>(mObj, "tileWidth"), as<unsigned int>(mObj, "tileHeight")};

				const auto& labels(as<Obj>(mObj, "labels"));
				for(auto iY(0u); iY < size(labels); ++iY)
					for(auto iX(0u); iX < size(labels[iY]); ++iX)
						mValue.setLabel(as<std::string>(labels[iY][iX]), {iX, iY});

				mValue.setTileSize(tileSize);
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				set(mObj, "tileWidth", mValue.getTileSize().x);
				set(mObj, "tileHeight", mValue.getTileSize().y);
				// TODO: labels
			}
		};
		template<> struct Converter<ssvs::BitmapFontData>
		{
			using T = ssvs::BitmapFontData;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				mValue.cellColumns = as<int>(mObj, "cellColumns");
				mValue.cellWidth = as<int>(mObj, "cellWidth");
				mValue.cellHeight = as<int>(mObj, "cellHeight");
				mValue.cellStart = as<int>(mObj, "cellStart");
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				set(mObj, "cellColumns", mValue.cellColumns);
				set(mObj, "cellWidth", mValue.cellWidth);
				set(mObj, "cellHeight", mValue.cellHeight);
				set(mObj, "cellStart", mValue.cellStart);
			}
		};
		template<> struct Converter<sf::Color>
		{
			using T = sf::Color;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				mValue.r = as<float>(mObj, 0);
				mValue.g = as<float>(mObj, 1);
				mValue.b = as<float>(mObj, 2);
				mValue.a = as<float>(mObj, 3);

			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				set(mObj, 0, mValue.r);
				set(mObj, 1, mValue.g);
				set(mObj, 2, mValue.b);
				set(mObj, 3, mValue.a);
			}
		};
	}
}


namespace ssvs
{
	class AssetManager;

	namespace Utils
	{
		Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Obj& mRoot);
		void loadAssetsFromJson(AssetManager& mAssetManager, const Path& mRootPath, const ssvuj::Obj& mRoot);
	}
}

#endif
#endif
