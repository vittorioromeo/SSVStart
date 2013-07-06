// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SFML/Audio.hpp>
#include "SSVStart/MusicPlayer/MusicPlayer.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	void MusicPlayer::play(Music& mMusic, Time mPlayingOffset)
	{
		stop();

		mMusic.setPlayingOffset(mPlayingOffset);
		mMusic.play();

		current = &mMusic;
	}
	void MusicPlayer::stop()					{ if(current != nullptr) current->stop(); }
	void MusicPlayer::pause()					{ if(current != nullptr) current->pause(); }
	void MusicPlayer::setVolume(int mVolume)	{ if(current != nullptr) current->setVolume(mVolume); }
	void MusicPlayer::setLoop(bool mLoop)		{ if(current != nullptr) current->setLoop(mLoop); }
}
