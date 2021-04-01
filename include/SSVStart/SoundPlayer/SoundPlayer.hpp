// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SSVUtils/MemoryManager/MemoryManager.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace ssvs
{

class SoundPlayer
{
private:
    float volume{100};
    ssvu::MonoManager<sf::Sound> sounds;

    void refreshVolume()
    {
        for(auto& s : sounds) s->setVolume(volume);
    }

public:
    enum class Mode
    {
        Overlap,
        Override,
        Abort
    };

    auto& play(sf::SoundBuffer& mSoundBuffer, Mode mMode = Mode::Overlap,
        float mPitch = 1.f)
    {
        for(const auto& s : sounds)
            if(s->getStatus() == sf::Sound::Status::Stopped) sounds.del(*s);

        if(mMode == Mode::Override)
        {
            stop(mSoundBuffer);
        }
        else if(mMode == Mode::Abort)
        {
            auto first(findFirst(mSoundBuffer));
            if(first != nullptr) return *first;
        }

        auto& sound(sounds.create(mSoundBuffer));
        sound.setVolume(volume);
        sound.setPitch(mPitch);
        sound.play();

        sounds.refresh();

        return sound;
    }

    void stop()
    {
        sounds.refresh();
        for(auto& s : sounds) s->stop();
    }

    void stop(const sf::SoundBuffer& mSoundBuffer)
    {
        sounds.refresh();
        for(auto& s : sounds)
            if(s->getBuffer() == &mSoundBuffer) s->stop();
    }

    void setVolume(float mVolume)
    {
        volume = mVolume;
        refreshVolume();
    }

    float getVolume() const noexcept
    {
        return volume;
    }

    bool isPlaying(const sf::SoundBuffer& mSoundBuffer)
    {
        return findFirst(mSoundBuffer) != nullptr;
    }

    sf::Sound* findFirst(const sf::SoundBuffer& mSoundBuffer)
    {
        sounds.refresh();
        for(const auto& s : sounds)
            if(s->getBuffer() == &mSoundBuffer) return s.get();
        return nullptr;
    }

    auto& getSounds() noexcept
    {
        return sounds;
    }

    const auto& getSounds() const noexcept
    {
        return sounds;
    }
};

} // namespace ssvs

// TODO: fading
// TODO: looping
// TODO: in-out loop markers
