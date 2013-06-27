// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_RESOURCEHOLDER
#define SSVS_ASSETS_RESOURCEHOLDER

#include <cassert>
#include <string>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SSVUtils/SSVUtils.h>

namespace ssvs
{
	namespace Internal
	{
		template<typename T> using Uptr = std::unique_ptr<T>;
		enum class Type{Load, Open, Image, SoundBuffer};

		static void fail() { throw std::runtime_error("Failed to load resource"); }
		template<typename T> static Uptr<T> create() { return ssvu::make_unique<T>(); }

		template<Type TT, typename T> struct Helper;
		template<typename T> struct Helper<Type::Load, T>
		{
			inline static Uptr<T> load(const std::string& mPath)				{ auto r(create<T>()); if(!r->loadFromFile(mPath))			fail(); return r; }
			inline static Uptr<T> load(const void* mData, std::size_t mSize)	{ auto r(create<T>()); if(!r->loadFromMemory(mData, mSize))	fail(); return r; }
			inline static Uptr<T> load(sf::InputStream& mStream)				{ auto r(create<T>()); if(!r->loadFromStream(mStream))		fail(); return r; }
		};
		template<typename T> struct Helper<Type::Open, T>
		{
			inline static Uptr<T> load(const std::string& mPath)				{ auto r(create<T>()); if(!r->openFromFile(mPath))			fail(); return r; }
			inline static Uptr<T> load(const void* mData, std::size_t mSize)	{ auto r(create<T>()); if(!r->openFromMemory(mData, mSize)) fail(); return r; }
			inline static Uptr<T> load(sf::InputStream& mStream)				{ auto r(create<T>()); if(!r->openFromStream(mStream))		fail(); return r; }
		};
		template<> struct Helper<Type::Image, sf::Texture>
		{
			using T = sf::Texture;
			inline static Uptr<T> load(const sf::Image& mImage)				{ auto r(create<T>()); if(!r->loadFromImage(mImage))		fail(); return r; }
		};
		template<> struct Helper<Type::SoundBuffer, sf::Sound>
		{
			using T = sf::Sound;
			inline static Uptr<T> load(const sf::SoundBuffer& mSoundBuffer)	{ return ssvu::make_unique<T>(mSoundBuffer); }
		};

		template<typename T> struct Loader // Most resources can be loaded only from Path, Memory or Stream
		{
			template<typename... TArgs> inline static Uptr<T> load(TArgs&&... mArgs) { return Helper<Type::Load, T>::load(mArgs...); }
		};
		template<> struct Loader<sf::Texture> // Texture can also be loaded from Image
		{
			using T = sf::Texture;
			inline static Uptr<T> load(const std::string& mPath)				{ return Helper<Type::Load, T>::load(mPath); }
			inline static Uptr<T> load(const void* mData, std::size_t mSize)	{ return Helper<Type::Load, T>::load(mData, mSize); }
			inline static Uptr<T> load(sf::InputStream& mStream)				{ return Helper<Type::Load, T>::load(mStream); }
			inline static Uptr<T> load(const sf::Image& mImage)					{ return Helper<Type::Image, T>::load(mImage); }
		};
		template<> struct Loader<sf::Sound> // Sound is not a real "resource", but it's easy to handle it as such - can be loaded only from SoundBuffer
		{
			using T = sf::Sound;
			inline static Uptr<T> load(const sf::SoundBuffer& mSoundBuffer)	{ return Helper<Type::SoundBuffer, T>::load(mSoundBuffer); }
		};
		template<> struct Loader<sf::Music> // Music can be opened from Path, Memory or Stream
		{
			using T = sf::Music;
			template<typename... TArgs> inline static Uptr<T> load(TArgs&&... mArgs)	{ return Helper<Type::Open, T>::load(mArgs...); }
		};


		template<typename T> class ResourceHolder
		{
			private:
				std::unordered_map<std::string, Uptr<T>> resources;

			public:
				template<typename... TArgs> T& load(const std::string& mId, TArgs&&... mArgs)
				{
					auto inserted(resources.insert(std::make_pair(mId, std::move(Loader<T>::load(mArgs...)))));
					assert(inserted.second); // Assertion error fires if inserting replaced an existing resource
					return *inserted.first->second;
				}

				T& operator[](const std::string& mId)
				{
					auto itr(resources.find(mId));
					assert(itr != std::end(resources)); // Assertion error fires if resource id wasn't found
					return *itr->second;
				}

				bool has(const std::string& mId) { return resources.count(mId) > 0; }
				std::unordered_map<std::string, Uptr<T>>& getResources() { return resources; }
		};
	}
}

#endif
