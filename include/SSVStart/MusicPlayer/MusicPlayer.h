// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_MUSICPLAYER
#define SSVS_MUSICPLAYER

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SSVUtils/SSVUtils.h>

namespace sf { class Music; }

namespace ssvs
{
	class MusicPlayer
	{
		private:
			sf::Music* current{nullptr};
			int volume{100};

		public:
			void play(sf::Music& mMusic, sf::Time mPlayingOffset = sf::seconds(0))
			{
				stop();

				mMusic.setPlayingOffset(mPlayingOffset);
				mMusic.setVolume(volume);
				mMusic.play();

				current = &mMusic;
			}
			inline void stop()					{ if(current != nullptr) current->stop(); }
			inline void pause()					{ if(current != nullptr) current->pause(); }
			inline void setVolume(int mVolume)	{ volume = mVolume; if(current != nullptr) current->setVolume(mVolume); }
			inline void setLoop(bool mLoop)		{ if(current != nullptr) current->setLoop(mLoop); }
			inline sf::Music* getCurrent()		{ return current; }
	};
}

#endif
