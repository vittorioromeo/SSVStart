// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVStart/SoundPlayer/SoundPlayer.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	void SoundPlayer::cleanUp()
	{
		for(const auto& s : memoryManager) if(s->getStatus() == Sound::Status::Stopped) memoryManager.del(s);
		memoryManager.cleanUp();
	}
	void SoundPlayer::refreshVolume() { for(auto& s : memoryManager) s->setVolume(volume); }

	void SoundPlayer::play(SoundBuffer& mSoundBuffer, Mode mMode)
	{
		cleanUp();

		switch(mMode)
		{
			case Mode::Overlap: break;
			case Mode::Override:
				for(const auto& s : memoryManager) if(s->getBuffer() == &mSoundBuffer) s->stop();
				break;
			case Mode::Abort:
				for(const auto& s : memoryManager) if(s->getBuffer() == &mSoundBuffer) return;
				break;
		}

		auto& sound(memoryManager.create(mSoundBuffer));
		sound.setVolume(volume);
		sound.play();
	}
	void SoundPlayer::stop() { for(auto& s : memoryManager) s->stop(); }
}
