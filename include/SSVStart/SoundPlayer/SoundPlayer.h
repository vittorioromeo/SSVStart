// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_SOUNDPLAYER
#define SSVS_SOUNDPLAYER

#include <SFML/Audio.hpp>
#include <SSVUtils/SSVUtils.h>

namespace ssvs
{
	class SoundPlayer
	{
		private:
			int volume{100};
			ssvu::MemoryManager<sf::Sound> memoryManager;

			void refreshVolume();
			void cleanUp();

		public:
			enum class Mode{Overlap, Override, Abort};

			void play(sf::SoundBuffer& mSoundBuffer, Mode mMode = Mode::Overlap);
			void stop();

			inline void setVolume(int mVolume)	{ volume = mVolume; refreshVolume(); }
			inline int getVolume()				{ return volume; }
	};
}

#endif
