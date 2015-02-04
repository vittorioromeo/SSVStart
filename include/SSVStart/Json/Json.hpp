// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_JSON
#define SSVS_JSON

#include <SFML/System.hpp>
#include <SSVUtils/Core/Core.hpp>
#include <SSVUtils/Json/Json.hpp>
#include "SSVStart/Tileset/Tileset.hpp"
#include "SSVStart/Animation/Animation.hpp"
#include "SSVStart/Input/Combo.hpp"
#include "SSVStart/Input/Trigger.hpp"
#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/Utils/Input.hpp"
#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Assets/AssetManager.hpp"

SSVJ_CNV_NAMESPACE()
{
	template<typename T> SSVJ_CNV(ssvs::Vec2<T>, mV, mX)	{ ssvj::cnvArr(mV, mX.x, mX.y); }													SSVJ_CNV_END()
	template<> SSVJ_CNV(ssvs::BitmapFontData, mV, mX)		{ ssvj::cnvArr(mV, mX.cellColumns, mX.cellWidth, mX.cellHeight, mX.cellStart); }	SSVJ_CNV_END()
	template<> SSVJ_CNV(sf::Color, mV, mX)					{ ssvj::cnvArr(mV, mX.r, mX.g, mX.b, mX.a); }										SSVJ_CNV_END()
	template<> SSVJ_CNV(ssvs::Input::Trigger, mV, mX)		{ ssvj::cnv(mV, mX.getCombos()); }													SSVJ_CNV_END()

	template<> struct Cnv<ssvs::KKey>
	{
		using T = ssvs::KKey;
		inline static void fromVal(const Val& mV, T& mX)	{ mX = ssvs::getKKey(mV.as<std::string>()); }
		inline static void toVal(Val& mV, const T& mX)		{ mV = ssvs::getKKeyName(mX); }
	};
	template<> struct Cnv<ssvs::MBtn>
	{
		using T = ssvs::MBtn;
		inline static void fromVal(const Val& mV, T& mX)	{ mX = ssvs::getMBtn(mV.as<std::string>()); }
		inline static void toVal(Val& mV, const T& mX)		{ mV = ssvs::getMBtnName(mX); }
	};
	template<> struct Cnv<ssvs::Input::Combo>
	{
		using T = ssvs::Input::Combo;
		inline static void fromVal(const Val& mV, T& mX)
		{
			for(const auto& i : mV.forArr())
			{
				const auto& name(i.as<std::string>());

				if(ssvs::isKKeyNameValid(name)) mX.addKey(i.as<ssvs::KKey>());
				else if(ssvs::isMBtnNameValid(name)) mX.addBtn(i.as<ssvs::MBtn>());
				else ssvu::lo("ssvs::getInputComboFromJSON") << "<" << i << "> is not a valid input name" << std::endl;
			}
		}
		inline static void toVal(Val& mV, const T& mX)
		{
			mV = Arr{};
			const auto& keys(mX.getKeys());
			const auto& btns(mX.getBtns());
			for(auto j(0u); j < ssvs::kKeyCount; ++j) if(ssvs::getKeyBit(keys, ssvs::KKey(j))) mV.emplace(ssvs::KKey(j));
			for(auto j(0u); j < ssvs::mBtnCount; ++j) if(ssvs::getBtnBit(btns, ssvs::MBtn(j))) mV.emplace(ssvs::MBtn(j));
		}
	};

	template<> struct Cnv<ssvs::Tileset>
	{
		using T = ssvs::Tileset;
		inline static void fromVal(const Val& mV, T& mX)
		{
			const auto& labels(mV["labels"]);
			for(auto iY(0u); iY < labels.getSizeArr(); ++iY)
				for(auto iX(0u); iX < labels[iY].getSizeArr(); ++iX)
					mX.setLabel(labels[iY][iX].as<std::string>(), {iX, iY});

			mX.setTileSize(mV["tileSize"].as<ssvs::Vec2u>());
		}
		inline static void toVal(Val& mV, const T& mX)
		{
			mV["tileSize"] = mX.getTileSize();

			mV["labels"] = Arr{};
			for(const auto& l : mX.getLabels()) mV["labels"][l.second.y][l.second.x] = l.first;
		}
	};
}
SSVJ_CNV_NAMESPACE_END()

namespace ssvs
{
	class AssetManager;

	inline auto getAnimationFromJson(const Tileset& mTileset, const ssvj::Val& mVal)
	{
		Animation::Type type{Animation::Type::Loop};

		const auto& jsonType(mVal.getIfHas<std::string>("type", ""));
		if(jsonType == "once") type = Animation::Type::Once;
		else if(jsonType == "pingpong") type = Animation::Type::PingPong;
		//else if(jsonType == "loop") type = Animation::Type::Loop;

		Animation result{type};

		for(const auto& i : mVal["frames"].forArr())
		{
			const auto& index(mTileset.getIdx(i[0].as<std::string>()));
			result.addStep({index, i[1].as<float>()});
		}

		result.setSpeed(mVal.getIfHas<float>("speed", 1.f));
		return result;
	}

	inline void loadAssetsFromJson(AssetManager& mAssetManager, const Path& mRootPath, const ssvj::Val& mVal)
	{
		using namespace std;

		for(const auto& f : mVal["fonts"].forArrAs<string>())			mAssetManager.load<sf::Font>(f, mRootPath + f);
		for(const auto& f : mVal["images"].forArrAs<string>())			mAssetManager.load<sf::Image>(f, mRootPath + f);
		for(const auto& f : mVal["textures"].forArrAs<string>())		mAssetManager.load<sf::Texture>(f, mRootPath + f);
		for(const auto& f : mVal["soundBuffers"].forArrAs<string>())	mAssetManager.load<sf::SoundBuffer>(f, mRootPath + f);
		for(const auto& f : mVal["musics"].forArrAs<string>())			mAssetManager.load<sf::Music>(f, mRootPath + f);
		for(const auto& f : mVal["shadersVertex"].forArrAs<string>())	mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Vertex, Impl::ShaderFromPath{});
		for(const auto& f : mVal["shadersFragment"].forArrAs<string>())	mAssetManager.load<sf::Shader>(f, mRootPath + f, sf::Shader::Type::Fragment, Impl::ShaderFromPath{});

		for(const auto& f : mVal["bitmapFonts"].forObj())
		{
			auto dv(ssvj::Val::fromFile(mRootPath + f.value[1].as<string>()));
			mAssetManager.load<BitmapFont>(f.key, mAssetManager.get<sf::Texture>(f.value[0].as<string>()), dv.as<BitmapFontData>());
		}
		for(const auto& f : mVal["tilesets"].forObj())
		{
			auto dv(ssvj::Val::fromFile(mRootPath + f.value.as<string>()));
			mAssetManager.load<Tileset>(f.key, dv.as<Tileset>());
		}
	}
}

#endif
