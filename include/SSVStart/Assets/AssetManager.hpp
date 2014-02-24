// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

#include <cassert>
#include <string>
#include <unordered_map>
#include <SSVUtils/Log/Log.hpp>
#include "SSVStart/Assets/Internal/ResourceHolder.hpp"

namespace sf { class Font; class Image; class Texture; class SoundBuffer; class Music; class Shader; }

namespace ssvs
{
	class BitmapFont;
	struct BitmapFontData;
	class Tileset;

	class AssetManager
	{
		private:
			Internal::ResourceHolder<sf::Font> fonts;
			Internal::ResourceHolder<sf::Image> images;
			Internal::ResourceHolder<sf::Texture> textures;
			Internal::ResourceHolder<sf::SoundBuffer> soundBuffers;
			Internal::ResourceHolder<sf::Music> musics;
			Internal::ResourceHolder<sf::Shader> shaders;
			Internal::ResourceHolder<BitmapFont> bitmapFonts;
			Internal::ResourceHolder<Tileset> tilesets;

			template<typename T> inline Internal::ResourceHolder<T>& getResourceHolder() noexcept;

		public:
			AssetManager() = default;

			template<typename T, typename... TArgs> inline T& load(const std::string& mId, TArgs&&... mArgs)
			{
				ssvu::lo("ssvs::AssetManager::load<T>") << mId << " resource loading" << std::endl;
				return getResourceHolder<T>().load(mId, std::forward<TArgs>(mArgs)...);
			}
			template<typename T> inline std::unordered_map<std::string, Uptr<T>>& getAll()	{ return getResourceHolder<T>().getResources(); }
			template<typename T> inline bool has(const std::string& mId)					{ return getResourceHolder<T>().has(mId); }
			template<typename T> inline T& get(const std::string& mId)						{ SSVU_ASSERT(has<T>(mId)); return getResourceHolder<T>()[mId]; }
	};

	template<> inline Internal::ResourceHolder<sf::Font>& AssetManager::getResourceHolder<sf::Font>() noexcept					{ return fonts; }
	template<> inline Internal::ResourceHolder<sf::Image>& AssetManager::getResourceHolder<sf::Image>() noexcept				{ return images; }
	template<> inline Internal::ResourceHolder<sf::Texture>& AssetManager::getResourceHolder<sf::Texture>() noexcept			{ return textures; }
	template<> inline Internal::ResourceHolder<sf::SoundBuffer>& AssetManager::getResourceHolder<sf::SoundBuffer>() noexcept	{ return soundBuffers; }
	template<> inline Internal::ResourceHolder<sf::Music>& AssetManager::getResourceHolder<sf::Music>() noexcept				{ return musics; }
	template<> inline Internal::ResourceHolder<sf::Shader>& AssetManager::getResourceHolder<sf::Shader>() noexcept				{ return shaders; }
	template<> inline Internal::ResourceHolder<BitmapFont>& AssetManager::getResourceHolder<BitmapFont>() noexcept				{ return bitmapFonts; }
	template<> inline Internal::ResourceHolder<Tileset>& AssetManager::getResourceHolder<Tileset>() noexcept					{ return tilesets; }
}

#endif
