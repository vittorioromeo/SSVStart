// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <SFML/Audio.hpp>
#include "SSVStart/SoundPlayer/SoundInstance.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	SoundInstance::SoundInstance(const SoundBuffer& mSoundBuffer, bool mManualLifetime) : soundBuffer(mSoundBuffer), sound{mSoundBuffer}, manualLifetime{mManualLifetime} { }

	const SoundBuffer& SoundInstance::getSoundBuffer()	{ return soundBuffer; }
	Sound& SoundInstance::getSound()					{ return sound; }
	bool SoundInstance::isManualLifetime()				{ return manualLifetime; }
}
