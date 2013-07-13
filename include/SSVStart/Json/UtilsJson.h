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
#include "SSVStart/BitmapFont/BitmapFontData.h"
#include "SSVStart/Utils/UtilsInput.h"

namespace ssvuj
{
	namespace Internal
	{
		template<> struct AsHelper<ssvs::Input::Combo>
		{
			inline static ssvs::Input::Combo as(const Impl& mValue)
			{
				ssvs::Input::Combo result;

				for(const auto& inputName : ssvuj::as<std::vector<std::string>>(mValue))
				{
					if(ssvs::Utils::isKeyNameValid(inputName)) result.addKey(ssvs::Utils::getKey(inputName));
					else if(ssvs::Utils::isButtonNameValid(inputName)) result.addButton(ssvs::Utils::getButton(inputName));
					else ssvu::log("<" + inputName + "> is not a valid input name", "ssvs::Utils::getInputComboFromJSON");
				}

				return result;
			}
		};
		template<> struct AsHelper<ssvs::Input::Trigger>
		{
			inline static ssvs::Input::Trigger as(const Impl& mValue)
			{
				ssvs::Input::Trigger result;

				for(const auto& comboArray : ssvuj::as<std::vector<ssvuj::Value>>(mValue))
					result.add(ssvuj::as<ssvs::Input::Combo>(comboArray));

				return result;
			}
		};
		template<> struct AsHelper<ssvs::Tileset>
		{
			inline static ssvs::Tileset as(const Impl& mValue)
			{
				ssvs::Vec2u tileSize{ssvuj::as<unsigned int>(mValue, "tileWidth"), ssvuj::as<unsigned int>(mValue, "tileHeight")};
				ssvs::Tileset result{tileSize};

				const ssvuj::Value& labels(ssvuj::as<ssvuj::Value>(mValue, "labels"));
				for(unsigned int iY{0}; iY < size(labels); ++iY)
					for(unsigned int iX{0}; iX < size(labels[iY]); ++iX)
						result.setLabel(ssvuj::as<std::string>(labels[iY][iX]), {iX, iY});

				return result;
			}
		};
		template<> struct AsHelper<ssvs::BitmapFontData>
		{
			inline static ssvs::BitmapFontData as(const Impl& mValue)
			{
				unsigned int cellColumns(ssvuj::as<int>(mValue, "cellColumns"));
				unsigned int cellWidth(ssvuj::as<int>(mValue, "cellWidth"));
				unsigned int cellHeight(ssvuj::as<int>(mValue, "cellHeight"));
				unsigned int cellStart(ssvuj::as<int>(mValue, "cellStart"));

				return {cellColumns, cellWidth, cellHeight, cellStart};
			}
		};
		template<> struct AsHelper<sf::Color>
		{
			inline static sf::Color as(const Impl& mValue)
			{
				return sf::Color(ssvuj::as<float>(mValue, 0), ssvuj::as<float>(mValue, 1), ssvuj::as<float>(mValue, 2), ssvuj::as<float>(mValue, 3));
			}
		};
	}

	template<> inline void set<ssvs::Input::Combo>(Impl& mRoot, const ssvs::Input::Combo& mValueToSet)
	{
		unsigned int i{0};
		const auto& keys(mValueToSet.getKeys());
		const auto& buttons(mValueToSet.getButtons());
		for(unsigned int j{0}; j < keys.size(); ++i, ++j) set(mRoot, i, ssvs::Utils::getKeyName(keys[j]));
		for(unsigned int j{0}; j < buttons.size(); ++i, ++j) set(mRoot, i, ssvs::Utils::getButtonName(buttons[j]));
	}
	template<> inline void set<ssvs::Input::Trigger>(Impl& mRoot, const ssvs::Input::Trigger& mValueToSet)
	{
		const auto& combos(mValueToSet.getCombos());
		for(unsigned int i{0}; i < combos.size(); ++i) set(mRoot, i, combos[i]);
	}
	template<> inline void set<ssvs::Tileset>(Impl& mRoot, const ssvs::Tileset& mValueToSet)
	{
		set(mRoot, "tileWidth", mValueToSet.getTileSize().x);
		set(mRoot, "tileHeight", mValueToSet.getTileSize().y);

		// TODO: labels
	}
	template<> inline void set<ssvs::BitmapFontData>(Impl& mRoot, const ssvs::BitmapFontData& mValueToSet)
	{
		set(mRoot, "cellColumns", mValueToSet.cellColumns);
		set(mRoot, "cellWidth", mValueToSet.cellWidth);
		set(mRoot, "cellHeight", mValueToSet.cellHeight);
		set(mRoot, "cellStart", mValueToSet.cellStart);
	}
	template<> inline void set<sf::Color>(Impl& mRoot, const sf::Color& mValueToSet)
	{
		set(mRoot, 0, mValueToSet.r);
		set(mRoot, 1, mValueToSet.g);
		set(mRoot, 2, mValueToSet.b);
		set(mRoot, 3, mValueToSet.a);
	}
}


namespace ssvs
{
	class AssetManager;

	namespace Utils
	{
		Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Value& mRoot);
		void loadAssetsFromJson(AssetManager& mAssetManager, const std::string& mRootPath, const ssvuj::Value& mRoot);
	}
}

#endif
#endif
