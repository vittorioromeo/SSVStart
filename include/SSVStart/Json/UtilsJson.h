// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_N_USE_JSON
#ifndef SSVS_JSON_UTILSJSON
#define SSVS_JSON_UTILSJSON

#include <future>
#include <SFML/System.hpp>
#include <SSVUtils/SSVUtils.h>
#include <SSVUtilsJson/SSVUtilsJson.h>
#include "SSVStart/Tileset/Tileset.h"
#include "SSVStart/Animation/Animation.h"
#include "SSVStart/Input/Combo.h"
#include "SSVStart/Input/Trigger.h"
#include "SSVStart/BitmapFont/BitmapFont.h"
#include "SSVStart/Utils/UtilsInput.h"
#include "SSVStart/Global/Typedefs.h"
#include "SSVStart/Assets/AssetManager.h"

namespace ssvs
{
	class AssetManager;

	inline Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Obj& mObj)
	{
		// TODO: get type from json
		Animation result{Animation::Type::Loop};

		for(const auto& f : ssvuj::get(mObj, "frames"))
		{
			const auto& index(mTileset.getIndex(ssvuj::as<std::string>(f, 0)));
			result.addStep({index, ssvuj::as<float>(f, 1)});
		}

		//result.setLoop(ssvuj::as<bool>(mObj, "loop", true));
		//result.setPingPong(ssvuj::as<bool>(mObj, "pingPong", false));
		//result.setReverse(ssvuj::as<bool>(mObj, "reverse", false));
		result.setSpeed(ssvuj::as<float>(mObj, "speed", 1.f));

		return result;
	}
	inline void loadAssetsFromJson(AssetManager& mAssetManager, const Path& mRootPath, const ssvuj::Obj& mObj)
	{
		using namespace std;
		using namespace ssvuj;

		for(const auto& f : as<vector<string>>(mObj, "fonts"))				mAssetManager.load<sf::Font>(f, mRootPath + f);
		for(const auto& f : as<vector<string>>(mObj, "images"))				mAssetManager.load<sf::Image>(f, mRootPath + f);
		for(const auto& f : as<vector<string>>(mObj, "textures"))			mAssetManager.load<sf::Texture>(f, mRootPath + f);
		for(const auto& f : as<vector<string>>(mObj, "soundBuffers"))		mAssetManager.load<sf::SoundBuffer>(f, mRootPath + f);
		for(const auto& f : as<vector<string>>(mObj, "musics"))				mAssetManager.load<sf::Music>(f, mRootPath + f);
		for(const auto& f : as<vector<string>>(mObj, "shadersVertex"))		mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Vertex, Internal::ShaderFromPath{});
		for(const auto& f : as<vector<string>>(mObj, "shadersFragment"))	mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Fragment, Internal::ShaderFromPath{});

		const auto& bfs(get(mObj, "bitmapFonts"));
			for(auto itr(begin(bfs)); itr != end(bfs); ++itr)
				mAssetManager.load<BitmapFont>(ssvuj::getKey(itr), mAssetManager.get<sf::Texture>(as<string>(*itr, 0)), as<BitmapFontData>(readFromFile(mRootPath + as<string>(*itr, 1))));

		const auto& tilesets(get(mObj, "tilesets"));
			for(auto itr(begin(tilesets)); itr != end(tilesets); ++itr)
				mAssetManager.load<Tileset>(ssvuj::getKey(itr), ssvuj::as<ssvs::Tileset>(ssvuj::readFromFile("Data/" + as<string>(*itr))));
	}
}

namespace ssvuj
{
	namespace Internal
	{
		template<typename TType> struct Converter<ssvs::Vec2<TType>>
		{
			using T = ssvs::Vec2<TType>;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extrArray(mObj, mValue.x, mValue.y); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archArray(mObj, mValue.x, mValue.y); }
		};
		template<> struct Converter<sf::Keyboard::Key>
		{
			using T = sf::Keyboard::Key;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::getKey(as<std::string>(mObj)); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ arch(mObj, ssvs::getKeyName(mValue)); }
		};
		template<> struct Converter<sf::Mouse::Button>
		{
			using T = sf::Mouse::Button;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::getButton(as<std::string>(mObj)); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ arch(mObj, ssvs::getButtonName(mValue)); }
		};
		template<> struct Converter<ssvs::Input::Combo>
		{
			using T = ssvs::Input::Combo;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				for(const auto& i : mObj)
				{
					if(ssvs::isKeyNameValid(as<std::string>(i))) mValue.addKey(as<sf::Keyboard::Key>(i));
					else if(ssvs::isButtonNameValid(as<std::string>(i))) mValue.addButton(as<sf::Mouse::Button>(i));
					else ssvu::lo("ssvs::getInputComboFromJSON") << "<" << i << "> is not a valid input name";
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
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extr(mObj, mValue.getCombos()); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ arch(mObj, mValue.getCombos()); }
		};
		template<> struct Converter<ssvs::Tileset>
		{
			using T = ssvs::Tileset;
			inline static void fromObj(T& mValue, const Obj& mObj)
			{
				const auto& labels(get(mObj, "labels"));
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
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extrArray(mObj, mValue.cellColumns, mValue.cellWidth, mValue.cellHeight, mValue.cellStart); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archArray(mObj, mValue.cellColumns, mValue.cellWidth, mValue.cellHeight, mValue.cellStart); }
		};
		template<> struct Converter<sf::Color>
		{
			using T = sf::Color;
			inline static void fromObj(T& mValue, const Obj& mObj)	{ extrArray(mObj, mValue.r, mValue.g, mValue.b, mValue.a); }
			inline static void toObj(Obj& mObj, const T& mValue)	{ archArray(mObj, mValue.r, mValue.g, mValue.b, mValue.a); }
		};
	}
}

#endif
#endif
