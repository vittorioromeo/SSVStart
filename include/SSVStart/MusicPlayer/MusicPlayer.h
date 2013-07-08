// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_MUSICPLAYER
#define SSVS_MUSICPLAYER

#include <SFML/System.hpp>
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
			void play(sf::Music& mMusic, sf::Time mPlayingOffset = sf::seconds(0));
			void stop();
			void pause();
			void setVolume(int mVolume);
			void setLoop(bool mLoop);
	};
}

#endif
