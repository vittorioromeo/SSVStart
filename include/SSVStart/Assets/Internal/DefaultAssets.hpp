// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Assets/Internal/Embedded.hpp"

#include <SSVUtils/Core/Utils/Containers.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Image.hpp>

namespace ssvs
{
namespace Impl
{
inline auto& getNullImage() noexcept
{
    struct NullImage
    {
        sf::Image data;
        NullImage()
        {
            data.create(32, 32, sf::Color::Magenta);
        }
    };

    static NullImage result;
    return result.data;
}

inline auto& getNullTexture() noexcept
{
    struct NullTexture
    {
        sf::Texture data;
        NullTexture()
        {
            data.loadFromImage(getNullImage());
        }
    };

    static NullTexture result;
    return result.data;
}

inline auto& getNullFont() noexcept
{
    struct NullFont
    {
        sf::Font data;

        NullFont()
        {
            data.loadFromMemory(__FreeSans_2strip_ttf,
                ssvu::getCArraySize(__FreeSans_2strip_ttf));
        }
    };

    static NullFont result;
    return result.data;
}

inline auto& getNullBitmapFont() noexcept
{
    struct NullBitmapFont
    {
        sf::Texture texture;
        ssvs::BitmapFont data;

        NullBitmapFont() : data(texture, BitmapFontData{16, 8, 10, 3})
        {
            texture.loadFromMemory(
                fontObStrokedData, ssvu::getCArraySize(fontObStrokedData));
        }
    };

    static NullBitmapFont result;
    return result.data;
}

inline auto& getNullSoundBuffer() noexcept
{
    static sf::SoundBuffer result;
    return result;
}

inline auto& getNullMusic() noexcept
{
    static sf::Music result;
    return result;
}

template <typename T>
struct DefResHelper;

#define SSVS_IMPL_SPECIALIZE_PDEF(mType) \
    template <>                          \
    struct DefResHelper<mType>           \
    {                                    \
        using T = mType;                 \
        static auto get() noexcept

SSVS_IMPL_SPECIALIZE_PDEF(sf::Font)
{
    return &getNullFont();
}
}; // namespace Impl
SSVS_IMPL_SPECIALIZE_PDEF(sf::Image)
{
    return &getNullImage();
}
}; // namespace ssvs
SSVS_IMPL_SPECIALIZE_PDEF(sf::Texture)
{
    return &getNullTexture();
}
}
;
SSVS_IMPL_SPECIALIZE_PDEF(sf::SoundBuffer)
{
    return &getNullSoundBuffer();
}
}
;
SSVS_IMPL_SPECIALIZE_PDEF(sf::Music)
{
    return &getNullMusic();
}
}
;
SSVS_IMPL_SPECIALIZE_PDEF(sf::Shader)
{
    return nullptr;
}
}
;
SSVS_IMPL_SPECIALIZE_PDEF(ssvs::BitmapFont)
{
    return &getNullBitmapFont();
}
}
;
SSVS_IMPL_SPECIALIZE_PDEF(ssvs::Tileset)
{
    return nullptr;
}
}
;

#undef SSVS_IMPL_SPECIALIZE_PDEF
}

template <typename T>
const auto& getDefaultAsset() noexcept
{
    return *Impl::DefResHelper<T>::get();
}
}
