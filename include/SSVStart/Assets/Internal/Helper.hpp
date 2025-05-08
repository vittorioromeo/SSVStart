// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/BitmapText/Impl/BitmapFont.hpp"
#include "SSVStart/Tileset/Tileset.hpp"

#include <SSVUtils/Core/Log/Log.hpp>
#include <SSVUtils/Core/FileSystem/Path.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Image.hpp>

#include <string>
#include <memory>
#include <cstddef>

namespace ssvs::Impl {

enum class Mode
{
    Load,
    Open,
    Image,
    Samples,
    Shader,
    BitmapFont,
    Tileset
};

template <bool>
struct ShaderDisambiguationTag
{};

using ShaderFromMemory = ShaderDisambiguationTag<true>;
using ShaderFromPath = ShaderDisambiguationTag<false>;

template <typename T, typename TF>
auto loadImpl(TF mFn, const std::string& mErr)
{
    auto result(std::make_unique<T>());
    if(mFn(result)) return result;

    // TODO: loErr?
    ssvu::lo("Failed to load resource - " + mErr);
    return std::unique_ptr<T>{nullptr};
}

template <Mode TT, typename T>
struct Helper;

template <typename T>
struct Helper<Mode::Load, T>
{
    static auto load(const ssvu::FileSystem::Path& mPath)
    {
        return loadImpl<T>([&mPath](auto& mP)
            { return mP->loadFromFile(mPath.getStr()); }, "from path");
    }
    static auto load(const void* mData, std::size_t mSize)
    {
        return loadImpl<T>([&mData, &mSize](auto& mP)
            { return mP->loadFromMemory(mData, mSize); }, "from memory");
    }
    static auto load(sf::InputStream& mStream)
    {
        return loadImpl<T>([&mStream](auto& mP)
            { return mP->loadFromStream(mStream); }, "from stream");
    }
};

template <typename T>
struct Helper<Mode::Open, T>
{
    static auto load(const ssvu::FileSystem::Path& mPath)
    {
        return loadImpl<T>([&mPath](auto& mP)
            { return mP->openFromFile(mPath); }, "from path");
    }
    static auto load(const void* mData, std::size_t mSize)
    {
        return loadImpl<T>([&mData, &mSize](auto& mP)
            { return mP->openFromMemory(mData, mSize); }, "from memory");
    }
    static auto load(sf::InputStream& mStream)
    {
        return loadImpl<T>([&mStream](auto& mP)
            { return mP->openFromStream(mStream); }, "from stream");
    }
};

template <>
struct Helper<Mode::Image, sf::Texture>
{
    using T = sf::Texture;
    static auto load(const sf::Image& mImage)
    {
        return loadImpl<T>([&mImage](auto& mP)
            { return mP->loadFromImage(mImage); }, "from image");
    }
};

template <>
struct Helper<Mode::Samples, sf::SoundBuffer>
{
    using T = sf::SoundBuffer;
    static auto load(const std::int16_t* mSamples, std::size_t mSampleCount,
        unsigned int mChannelCount, unsigned int mSampleRate)
    {
        return loadImpl<T>(
            [&mSamples, &mSampleCount, &mChannelCount, &mSampleRate](auto& mP)
            {
                return mP->loadFromSamples(
                    mSamples, mSampleCount, mChannelCount, mSampleRate);
            },
            "from samples");
    }
};

template <>
struct Helper<Mode::Shader, sf::Shader>
{
    using T = sf::Shader;
    static auto load(const ssvu::FileSystem::Path& mPath,
        sf::Shader::Type mType, ShaderFromPath)
    {
        return loadImpl<T>([&mPath, &mType](auto& mP)
            { return mP->loadFromFile(mPath.getStr(), mType); },
            "shader from path");
    }
    static auto load(const ssvu::FileSystem::Path& mPathVertex,
        const ssvu::FileSystem::Path& mPathFragment, ShaderFromPath)
    {
        return loadImpl<T>(
            [&mPathVertex, &mPathFragment](auto& mP)
            {
                return mP->loadFromFile(
                    mPathVertex.getStr(), mPathFragment.getStr());
            },
            "shader from path (2)");
    }
    static auto load(
        const std::string& mShader, sf::Shader::Type mType, ShaderFromMemory)
    {
        return loadImpl<T>([&mShader, &mType](auto& mP)
            { return mP->loadFromMemory(mShader, mType); },
            "shader from memory");
    }
    static auto load(const std::string& mShaderVertex,
        const std::string& mShaderFragment, ShaderFromMemory)
    {
        return loadImpl<T>([&mShaderVertex, &mShaderFragment](auto& mP)
            { return mP->loadFromMemory(mShaderVertex, mShaderFragment); },
            "shader from memory (2)");
    }
    static auto load(sf::InputStream& mStream, sf::Shader::Type mType)
    {
        return loadImpl<T>([&mStream, &mType](auto& mP)
            { return mP->loadFromStream(mStream, mType); },
            "shader from stream");
    }
    static auto load(
        sf::InputStream& mStreamVertex, sf::InputStream& mStreamFragment)
    {
        return loadImpl<T>([&mStreamVertex, &mStreamFragment](auto& mP)
            { return mP->loadFromStream(mStreamVertex, mStreamFragment); },
            "shader from stream (2)");
    }
};

template <>
struct Helper<Mode::BitmapFont, BitmapFont>
{
    using T = BitmapFont;
    static auto load(const sf::Texture& mTexture, const BitmapFontData& mData)
    {
        return std::make_unique<T>(mTexture, mData);
    }
};

template <>
struct Helper<Mode::Tileset, Tileset>
{
    using T = Tileset;
    static auto load(const Tileset& mTileset)
    {
        return std::make_unique<T>(mTileset);
    }
};

} // namespace ssvs::Impl
