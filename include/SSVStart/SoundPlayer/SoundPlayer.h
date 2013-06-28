// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_SOUNDPLAYER
#define SSVS_SOUNDPLAYER

#include <SSVUtils/SSVUtils.h>

namespace sf
{
	class SoundBuffer;
	class Sound;
}

namespace ssvs
{
	class SoundInstance;

	class SoundPlayer
	{
		private:
			ssvu::MemoryManager<SoundInstance> memoryManager;

		public:
			void cleanUp();
			void del(SoundInstance& mSoundInstance);
			void stop();
			void setVolume(int mVolume);

			SoundInstance& create(const sf::SoundBuffer& mSoundBuffer, bool mManualLifetime = false);
	};
}

#endif
