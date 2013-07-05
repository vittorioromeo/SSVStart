// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SFML/Audio.hpp>
#include "SSVStart/SoundPlayer/SoundInstance.h"
#include "SSVStart/SoundPlayer/SoundPlayer.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	void SoundPlayer::cleanUp()
	{
		for(const auto& s : memoryManager) if(!s->isManualLifetime() && s->getSound().getStatus() == Sound::Status::Stopped) memoryManager.del(s);
		memoryManager.cleanUp();
	}
	void SoundPlayer::del(SoundInstance& mSoundInstance) { memoryManager.del(&mSoundInstance); }
	void SoundPlayer::stop() { for(auto& s : memoryManager) s->getSound().stop(); }
	void SoundPlayer::setVolume(int mVolume) { for(auto& s : memoryManager) s->getSound().setVolume(mVolume); }
	void SoundPlayer::play(SoundInstance& mSoundInstance) { mSoundInstance.getSound().play(); }

	SoundInstance& SoundPlayer::create(const SoundBuffer& mSoundBuffer, bool mManualLifetime) { cleanUp(); return memoryManager.create(mSoundBuffer, mManualLifetime); }


}
