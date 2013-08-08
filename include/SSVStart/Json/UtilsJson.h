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

namespace ssvuj
{
	namespace Internal
	{
		template<> struct FromJson<ssvs::Input::Combo>
		{
			inline static ssvs::Input::Combo conv(const Obj& mObj)
			{
				ssvs::Input::Combo result;

				for(const auto& inputName : as<std::vector<std::string>>(mObj))
				{
					if(ssvs::Utils::isKeyNameValid(inputName)) result.addKey(ssvs::Utils::getKey(inputName));
					else if(ssvs::Utils::isButtonNameValid(inputName)) result.addButton(ssvs::Utils::getButton(inputName));
					else ssvu::lo << ssvu::lt("ssvs::Utils::getInputComboFromJSON") << "<" << inputName << "> is not a valid input name";
				}

				return result;
			}
		};
		template<> struct FromJson<ssvs::Input::Trigger>
		{
			inline static ssvs::Input::Trigger conv(const Obj& mObj)
			{
				ssvs::Input::Trigger result;

				for(const auto& comboArray : as<std::vector<ssvuj::Obj>>(mObj))
					result.add(as<ssvs::Input::Combo>(comboArray));

				return result;
			}
		};
		template<> struct FromJson<ssvs::Tileset>
		{
			inline static ssvs::Tileset conv(const Obj& mObj)
			{
				ssvs::Vec2u tileSize{as<unsigned int>(mObj, "tileWidth"), as<unsigned int>(mObj, "tileHeight")};
				ssvs::Tileset result{tileSize};

				const ssvuj::Obj& labels(as<ssvuj::Obj>(mObj, "labels"));
				for(unsigned int iY{0}; iY < size(labels); ++iY)
					for(unsigned int iX{0}; iX < size(labels[iY]); ++iX)
						result.setLabel(as<std::string>(labels[iY][iX]), {iX, iY});

				return result;
			}
		};
		template<> struct FromJson<ssvs::BitmapFontData>
		{
			inline static ssvs::BitmapFontData conv(const Obj& mObj)
			{
				unsigned int cellColumns(as<int>(mObj, "cellColumns"));
				unsigned int cellWidth(as<int>(mObj, "cellWidth"));
				unsigned int cellHeight(as<int>(mObj, "cellHeight"));
				unsigned int cellStart(as<int>(mObj, "cellStart"));

				return {cellColumns, cellWidth, cellHeight, cellStart};
			}
		};
		template<> struct FromJson<sf::Color>
		{
			inline static sf::Color conv(const Obj& mObj)
			{
				return sf::Color(as<float>(mObj, 0), as<float>(mObj, 1), as<float>(mObj, 2), as<float>(mObj, 3));
			}
		};

		template<> struct ToJson<ssvs::Input::Combo>
		{
			inline static Obj conv(const ssvs::Input::Combo& mValue)
			{
				Obj result;
				auto i(0u);
				const auto& keys(mValue.getKeys());
				const auto& buttons(mValue.getButtons());
				for(auto j(0u); j < keys.size(); ++i, ++j) set(result, i, ssvs::Utils::getKeyName(keys[j]));
				for(auto j(0u); j < buttons.size(); ++i, ++j) set(result, i, ssvs::Utils::getButtonName(buttons[j]));
				return result;
			}
		};

		template<> struct ToJson<ssvs::Input::Trigger>
		{
			inline static Obj conv(const ssvs::Input::Trigger& mValue)
			{
				Obj result;
				const auto& combos(mValue.getCombos());
				for(auto i(0u); i < combos.size(); ++i) set(result, i, combos[i]);
				return result;
			}
		};
		template<> struct ToJson<ssvs::Tileset>
		{
			inline static Obj conv(const ssvs::Tileset& mValue)
			{
				Obj result;
				set(result, "tileWidth", mValue.getTileSize().x);
				set(result, "tileHeight", mValue.getTileSize().y);
				// TODO: labels
				return result;
			}
		};
		template<> struct ToJson<ssvs::BitmapFontData>
		{
			inline static Obj conv(const ssvs::BitmapFontData& mValue)
			{
				Obj result;
				set(result, "cellColumns", mValue.cellColumns);
				set(result, "cellWidth", mValue.cellWidth);
				set(result, "cellHeight", mValue.cellHeight);
				set(result, "cellStart", mValue.cellStart);
				return result;
			}
		};
		template<> struct ToJson<sf::Color>
		{
			inline static Obj conv(const sf::Color& mValue)
			{
				Obj result;
				set(result, 0, mValue.r);
				set(result, 1, mValue.g);
				set(result, 2, mValue.b);
				set(result, 3, mValue.a);
				return result;
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
		void loadAssetsFromJson(AssetManager& mAssetManager, const std::string& mRootPath, const ssvuj::Obj& mRoot);
	}
}

#endif
#endif
