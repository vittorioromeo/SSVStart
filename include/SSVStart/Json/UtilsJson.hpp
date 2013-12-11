// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_N_USE_JSON
#ifndef SSVS_JSON_UTILSJSON
#define SSVS_JSON_UTILSJSON

#include <future>
#include <SFML/System.hpp>
#include <SSVUtils/Log/Log.hpp>
#include <SSVUtilsJson/SSVUtilsJson.hpp>
#include "SSVStart/Tileset/Tileset.hpp"
#include "SSVStart/Animation/Animation.hpp"
#include "SSVStart/Input/Combo.hpp"
#include "SSVStart/Input/Trigger.hpp"
#include "SSVStart/BitmapText/BitmapFont.hpp"
#include "SSVStart/Utils/UtilsInput.hpp"
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Assets/AssetManager.hpp"

namespace ssvs
{
	class AssetManager;

	inline Animation getAnimationFromJson(const Tileset& mTileset, const ssvuj::Obj& mObj)
	{
		Animation::Type type{Animation::Type::Loop};

		std::string jsonType{ssvuj::getAs<std::string>(mObj, "type", "")};
		if(jsonType == "once") type = Animation::Type::Once;
		else if(jsonType == "loop") type = Animation::Type::Loop;
		else if(jsonType == "pingpong") type = Animation::Type::PingPong;

		Animation result{type};

		for(const auto& f : ssvuj::get(mObj, "frames"))
		{
			const auto& index(mTileset.getIdx(ssvuj::getAs<std::string>(f, 0)));
			result.addStep({index, ssvuj::getAs<float>(f, 1)});
		}

		result.setSpeed(ssvuj::getAs<float>(mObj, "speed", 1.f));
		return result;
	}
	inline void loadAssetsFromJson(AssetManager& mAssetManager, const Path& mRootPath, const ssvuj::Obj& mObj)
	{
		using namespace std;
		using namespace ssvuj;

		for(const auto& f : getAs<vector<string>>(mObj, "fonts"))				mAssetManager.load<sf::Font>(f, mRootPath + f);
		for(const auto& f : getAs<vector<string>>(mObj, "images"))				mAssetManager.load<sf::Image>(f, mRootPath + f);
		for(const auto& f : getAs<vector<string>>(mObj, "textures"))			mAssetManager.load<sf::Texture>(f, mRootPath + f);
		for(const auto& f : getAs<vector<string>>(mObj, "soundBuffers"))		mAssetManager.load<sf::SoundBuffer>(f, mRootPath + f);
		for(const auto& f : getAs<vector<string>>(mObj, "musics"))				mAssetManager.load<sf::Music>(f, mRootPath + f);
		for(const auto& f : getAs<vector<string>>(mObj, "shadersVertex"))		mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Vertex, Internal::ShaderFromPath{});
		for(const auto& f : getAs<vector<string>>(mObj, "shadersFragment"))	mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Fragment, Internal::ShaderFromPath{});

		const auto& bfs(get(mObj, "bitmapFonts"));
			for(auto itr(begin(bfs)); itr != end(bfs); ++itr)
				mAssetManager.load<BitmapFont>(ssvuj::getKey(itr), mAssetManager.get<sf::Texture>(getAs<string>(*itr, 0)), getAs<BitmapFontData>(readFromFile(mRootPath + getAs<string>(*itr, 1))));

		const auto& tilesets(get(mObj, "tilesets"));
			for(auto itr(begin(tilesets)); itr != end(tilesets); ++itr)
				mAssetManager.load<Tileset>(ssvuj::getKey(itr), ssvuj::getAs<ssvs::Tileset>(ssvuj::readFromFile("Data/" + getAs<string>(*itr))));
	}
}

namespace ssvuj
{
	template<typename TType> struct Converter<ssvs::Vec2<TType>>
	{
		using T = ssvs::Vec2<TType>;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ extrArray(mObj, mValue.x, mValue.y); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ archArray(mObj, mValue.x, mValue.y); }
	};
	template<> struct Converter<ssvs::KKey>
	{
		using T = ssvs::KKey;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::getKey(getAs<std::string>(mObj)); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ arch(mObj, ssvs::getKeyName(mValue)); }
	};
	template<> struct Converter<ssvs::MBtn>
	{
		using T = ssvs::MBtn;
		inline static void fromObj(T& mValue, const Obj& mObj)	{ mValue = ssvs::getBtn(getAs<std::string>(mObj)); }
		inline static void toObj(Obj& mObj, const T& mValue)	{ arch(mObj, ssvs::getBtnName(mValue)); }
	};
	template<> struct Converter<ssvs::Input::Combo>
	{
		using T = ssvs::Input::Combo;
		inline static void fromObj(T& mValue, const Obj& mObj)
		{
			for(const auto& i : mObj)
			{
				if(ssvs::isKeyNameValid(getAs<std::string>(i))) mValue.addKey(getAs<ssvs::KKey>(i));
				else if(ssvs::isBtnNameValid(getAs<std::string>(i))) mValue.addBtn(getAs<ssvs::MBtn>(i));
				else ssvu::lo("ssvs::getInputComboFromJSON") << "<" << i << "> is not a valid input name";
			}
		}
		inline static void toObj(Obj& mObj, const T& mValue)
		{
			auto i(0u);
			const auto& keys(mValue.getKeys());
			const auto& btns(mValue.getBtns());
			for(auto j(0u); j < ssvs::KKeyCount; ++j) if(keys[j + 1]) set(mObj, i++, ssvs::KKey(j));
			for(auto j(0u); j < ssvs::MBtnCount; ++j) if(btns[j + 1]) set(mObj, i++, ssvs::MBtn(j));
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
					mValue.setLabel(getAs<std::string>(labels[iY][iX]), {iX, iY});

			mValue.setTileSize(getAs<ssvs::Vec2u>(mObj, "tileSize"));
		}
		inline static void toObj(Obj& mObj, const T& mValue)
		{
			set(mObj, "tileSize", mValue.getTileSize());

			auto& labels(get(mObj, "labels"));
			for(const auto& l : mValue.labels)
				set(labels[l.second.y][l.second.x], l.first);
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

#endif
#endif
