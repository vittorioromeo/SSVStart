// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Assets/Internal/ResourceHolder.hpp"

#include <SSVUtils/Core/Log/Log.hpp>
#include <SSVUtils/Core/MPL/MPL.hpp>

#include <string>
#include <tuple>

namespace sf {

class Font;
class Image;
class Texture;
class SoundBuffer;
class Music;
class Shader;

} // namespace sf

namespace ssvs {

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
    auto& getRH() noexcept
    {
        return std::get<RHType<T>>(resTpl);
    }

public:
    template <typename T, typename... TArgs>
    T& load(const std::string& mId, TArgs&&... mArgs)
    {
        ssvu::lo("ssvs::AssetManager::load<T>") << mId << " resource loading\n";
        return getRH<T>().load(mId, FWD(mArgs)...);
    }

    template <typename T>
    auto& getAll()
    {
        return getRH<T>().getResources();
    }

    template <typename T>
    bool has(const std::string& mId)
    {
        return getRH<T>().has(mId);
    }

    template <typename T>
    T& get(const std::string& mId)
    {
        return getRH<T>()[mId];
    }
};

class DefaultAssetManager : public AssetManager<RHPolicyDefault>
{};

} // namespace ssvs
