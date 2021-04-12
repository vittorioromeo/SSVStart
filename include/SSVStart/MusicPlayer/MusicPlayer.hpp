// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>

#include <cassert>

namespace ssvs
{

class MusicPlayer
{
private:
    sf::Music* current{nullptr};
    float volume{100};
    bool loop{true};

public:
    void play(
        sf::Music& mMusic, const sf::Time& mPlayingOffset = sf::seconds(0))
    {
        assert(mPlayingOffset <= mMusic.getDuration());

        stop();

        mMusic.setVolume(volume);
        mMusic.setLoop(true);
        mMusic.play();
        mMusic.setPlayingOffset(mPlayingOffset);

        current = &mMusic;
    }
    void stop()
    {
        if(current != nullptr) current->stop();
    }
    void pause()
    {
        if(current != nullptr) current->pause();
    }
    void resume()
    {
        if(current != nullptr) current->play();
    }

    void setVolume(float mVolume)
    {
        volume = mVolume;
        if(current != nullptr) current->setVolume(mVolume);
    }
    void setLoop(bool mLoop)
    {
        loop = mLoop;
        if(current != nullptr) current->setLoop(loop);
    }

    auto getCurrent() noexcept
    {
        return current;
    }
    auto getVolume() const noexcept
    {
        return volume;
    }
    bool getLoop() const noexcept
    {
        return loop;
    }
};

} // namespace ssvs
