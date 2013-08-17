// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

#include <cassert>
#include <string>
#include <unordered_map>
#include <SSVUtils/SSVUtils.h>
#include "SSVStart/Assets/Internal/ResourceHolder.h"

namespace sf { class Font; class Image; class Texture; class SoundBuffer; class Music; class Shader; }

namespace ssvs
{
	class BitmapFont;
	struct BitmapFontData;

	class AssetManager
	{
		private:
			Internal::ResourceHolder<sf::Font> fonts;
			Internal::ResourceHolder<sf::Image> images;
			Internal::ResourceHolder<sf::Texture> textures;
			Internal::ResourceHolder<sf::SoundBuffer> soundBuffers;
			Internal::ResourceHolder<sf::Music> musics;
			Internal::ResourceHolder<sf::Shader> shaders;
			Internal::ResourceHolder<ssvs::BitmapFont> bitmapFonts;

			template<typename T> inline Internal::ResourceHolder<T>& getResourceHolder();

		public:
			AssetManager() = default;

			template<typename T, typename... TArgs> inline T& load(const std::string& mId, TArgs&&... mArgs)
			{
				// TODO: logging not thread safe!
				ssvu::lo << ssvu::lt("ssvs::AssetManager::load<T>") << mId << " resource loading" << std::endl;
				return getResourceHolder<T>().load(mId, std::forward<TArgs>(mArgs)...);
			}
			template<typename T> inline std::unordered_map<std::string, Uptr<T>>& getAll()	{ return getResourceHolder<T>().getResources(); }
			template<typename T> inline bool has(const std::string& mId)					{ return getResourceHolder<T>().has(mId); }
			template<typename T> inline T& get(const std::string& mId)						{ assert(has<T>(mId)); return getResourceHolder<T>()[mId]; }
	};

	template<> inline Internal::ResourceHolder<sf::Font>& AssetManager::getResourceHolder<sf::Font>()				{ return fonts; }
	template<> inline Internal::ResourceHolder<sf::Image>& AssetManager::getResourceHolder<sf::Image>()				{ return images; }
	template<> inline Internal::ResourceHolder<sf::Texture>& AssetManager::getResourceHolder<sf::Texture>()			{ return textures; }
	template<> inline Internal::ResourceHolder<sf::SoundBuffer>& AssetManager::getResourceHolder<sf::SoundBuffer>()	{ return soundBuffers; }
	template<> inline Internal::ResourceHolder<sf::Music>& AssetManager::getResourceHolder<sf::Music>()				{ return musics; }
	template<> inline Internal::ResourceHolder<sf::Shader>& AssetManager::getResourceHolder<sf::Shader>()			{ return shaders; }
	template<> inline Internal::ResourceHolder<BitmapFont>& AssetManager::getResourceHolder<BitmapFont>()			{ return bitmapFonts; }
}

#endif
