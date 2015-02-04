// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

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
			Impl::ResourceHolder<sf::Font> fonts;
			Impl::ResourceHolder<sf::Image> images;
			Impl::ResourceHolder<sf::Texture> textures;
			Impl::ResourceHolder<sf::SoundBuffer> soundBuffers;
			Impl::ResourceHolder<sf::Music> musics;
			Impl::ResourceHolder<sf::Shader> shaders;
			Impl::ResourceHolder<BitmapFont> bitmapFonts;
			Impl::ResourceHolder<Tileset> tilesets;

			template<typename T> inline Impl::ResourceHolder<T>& getResourceHolder() noexcept;

		public:
			template<typename T, typename... TArgs> inline T& load(const std::string& mId, TArgs&&... mArgs)
			{
				ssvu::lo("ssvs::AssetManager::load<T>") << mId << " resource loading\n";
				return getResourceHolder<T>().load(mId, SSVU_FWD(mArgs)...);
			}
			template<typename T> inline auto& getAll()						{ return getResourceHolder<T>().getResources(); }
			template<typename T> inline bool has(const std::string& mId)	{ return getResourceHolder<T>().has(mId); }
			template<typename T> inline T& get(const std::string& mId)		{ SSVU_ASSERT(has<T>(mId)); return getResourceHolder<T>()[mId]; }
	};

	template<> inline Impl::ResourceHolder<sf::Font>& AssetManager::getResourceHolder<sf::Font>() noexcept					{ return fonts; }
	template<> inline Impl::ResourceHolder<sf::Image>& AssetManager::getResourceHolder<sf::Image>() noexcept				{ return images; }
	template<> inline Impl::ResourceHolder<sf::Texture>& AssetManager::getResourceHolder<sf::Texture>() noexcept			{ return textures; }
	template<> inline Impl::ResourceHolder<sf::SoundBuffer>& AssetManager::getResourceHolder<sf::SoundBuffer>() noexcept	{ return soundBuffers; }
	template<> inline Impl::ResourceHolder<sf::Music>& AssetManager::getResourceHolder<sf::Music>() noexcept				{ return musics; }
	template<> inline Impl::ResourceHolder<sf::Shader>& AssetManager::getResourceHolder<sf::Shader>() noexcept				{ return shaders; }
	template<> inline Impl::ResourceHolder<BitmapFont>& AssetManager::getResourceHolder<BitmapFont>() noexcept				{ return bitmapFonts; }
	template<> inline Impl::ResourceHolder<Tileset>& AssetManager::getResourceHolder<Tileset>() noexcept					{ return tilesets; }
}

#endif
