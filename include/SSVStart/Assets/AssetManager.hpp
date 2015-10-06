// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_ASSETS_ASSETMANAGER
#define SSVS_ASSETS_ASSETMANAGER

#include "SSVStart/Assets/Internal/ResourceHolder.hpp"

namespace sf
{
    class Font;
    class Image;
    class Texture;
    class SoundBuffer;
    class Music;
    class Shader;
}

namespace ssvs
{
    class BitmapFont;
    struct BitmapFontData;
    class Tileset;

    template <typename TPolicyMissing = RHPolicyDefault>
    class AssetManager
    {
    public:
        using ResourceTypes = ssvu::MPL::List<sf::Font, sf::Image, sf::Texture,
            sf::SoundBuffer, sf::Music, sf::Shader, BitmapFont, Tileset>;
        template <typename T>
        using RHType = Impl::ResourceHolder<T, TPolicyMissing>;
        using ResTpl = typename ResourceTypes::Apply<RHType>::AsTpl;

    private:
        ResTpl resTpl;
        template <typename T>
        inline auto& getRH() noexcept
        {
            return std::get<RHType<T>>(resTpl);
        }

    public:
        template <typename T, typename... TArgs>
        inline T& load(const std::string& mId, TArgs&&... mArgs)
        {
            ssvu::lo("ssvs::AssetManager::load<T>") << mId
                                                    << " resource loading\n";
            return getRH<T>().load(mId, FWD(mArgs)...);
        }

        template <typename T>
        inline auto& getAll()
        {
            return getRH<T>().getResources();
        }
        template <typename T>
        inline bool has(const std::string& mId)
        {
            return getRH<T>().has(mId);
        }
        template <typename T>
        inline T& get(const std::string& mId)
        {
            return getRH<T>()[mId];
        }
    };
}

#endif
