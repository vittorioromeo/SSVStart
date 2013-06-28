// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_SOUNDPLAYER_SOUNDINSTANCE
#define SSVS_SOUNDPLAYER_SOUNDINSTANCE

namespace sf
{
	class SoundBuffer;
	class Sound;
}

namespace ssvs
{
	class SoundInstance
	{
		private:
			const sf::SoundBuffer& soundBuffer;
			sf::Sound sound;
			bool manualLifetime{false};

		public:
			SoundInstance(const sf::SoundBuffer& mSoundBuffer, bool mManualLifetime = false);

			const sf::SoundBuffer& getSoundBuffer();
			sf::Sound& getSound();
			bool isManualLifetime();
	};
}

#endif
