// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_MUSICPLAYER
#define SSVS_MUSICPLAYER

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SSVUtils/Core/Core.hpp>

namespace ssvs
{
	class MusicPlayer
	{
		private:
			sf::Music* current{nullptr};
			float volume{100};
			bool loop{true};

		public:
			inline void play(sf::Music& mMusic, const sf::Time& mPlayingOffset = sf::seconds(0))
			{
				SSVU_ASSERT(mPlayingOffset <= mMusic.getDuration());

				stop();

				mMusic.setVolume(volume);
				mMusic.setLoop(true);
				mMusic.play();
				mMusic.setPlayingOffset(mPlayingOffset);

				current = &mMusic;
			}
			inline void stop()	{ if(current != nullptr) current->stop(); }
			inline void pause()	{ if(current != nullptr) current->pause(); }

			inline void setVolume(float mVolume)	{ volume = mVolume; if(current != nullptr) current->setVolume(mVolume); }
			inline void setLoop(bool mLoop)			{ loop = mLoop;		if(current != nullptr) current->setLoop(loop); }

			inline auto getCurrent() noexcept		{ return current; }
			inline auto getVolume() const noexcept	{ return volume; }
			inline bool getLoop() const noexcept	{ return loop; }
	};
}

#endif
