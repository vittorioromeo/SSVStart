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
		template<typename TType> struct Converter<ssvs::Vec2<TType>>
		{
			using T = ssvs::Vec2<TType>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extract(mObj, mValue.x, mValue.y); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archive(mObj, mValue.x, mValue.y); }
		};
		template<> struct Converter<sf::Keyboard::Key>
		{
			using T = sf::Keyboard::Key;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::Utils::getKey(as<std::string>(mObj)); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ set(mObj, ssvs::Utils::getKeyName(mValue)); }
		};
		template<> struct Converter<sf::Mouse::Button>
		{
			using T = sf::Mouse::Button;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::Utils::getButton(as<std::string>(mObj)); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ set(mObj, ssvs::Utils::getButtonName(mValue)); }
		};
		template<> struct Converter<ssvs::Input::Combo>
		{
			using T = ssvs::Input::Combo;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				for(const auto& i : as<std::vector<Obj>>(mObj))
				{
					if(ssvs::Utils::isKeyNameValid(as<std::string>(i))) mValue.addKey(as<sf::Keyboard::Key>(i));
					else if(ssvs::Utils::isButtonNameValid(as<std::string>(i))) mValue.addButton(as<sf::Mouse::Button>(i));
					else ssvu::lo << ssvu::lt("ssvs::Utils::getInputComboFromJSON") << "<" << i << "> is not a valid input name";
				}
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				auto i(0u);
				const auto& keys(mValue.getKeys());
				const auto& buttons(mValue.getButtons());
				for(auto j(0u); j < keys.size(); ++i, ++j) set(mObj, i, keys[j]);
				for(auto j(0u); j < buttons.size(); ++i, ++j) set(mObj, i, buttons[j]);
			}
		};
		template<> struct Converter<ssvs::Input::Trigger>
		{
			using T = ssvs::Input::Trigger;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ for(const auto& c : as<std::vector<ssvs::Input::Combo>>(mObj)) mValue.add(c); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ set(mObj, mValue.getCombos()); }
		};
		template<> struct Converter<ssvs::Tileset>
		{
			using T = ssvs::Tileset;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				const auto& labels(as<Obj>(mObj, "labels"));
				for(auto iY(0u); iY < size(labels); ++iY)
					for(auto iX(0u); iX < size(labels[iY]); ++iX)
						mValue.setLabel(as<std::string>(labels[iY][iX]), {iX, iY});

				mValue.setTileSize(as<ssvs::Vec2u>(mObj, "tileSize"));
			}
			inline static void toObj(Obj& mObj, const T& mValue)
			{
				set(mObj, "tileSize", mValue.getTileSize());
				// TODO: labels
			}
		};
		template<> struct Converter<ssvs::BitmapFontData>
		{
			using T = ssvs::BitmapFontData;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extract(mObj, mValue.cellColumns, mValue.cellWidth, mValue.cellHeight, mValue.cellStart); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archive(mObj, mValue.cellColumns, mValue.cellWidth, mValue.cellHeight, mValue.cellStart); }
		};
		template<> struct Converter<sf::Color>
		{
			using T = sf::Color;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extract(mObj, mValue.r, mValue.g, mValue.b, mValue.a); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archive(mObj, mValue.r, mValue.g, mValue.b, mValue.a); }
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
