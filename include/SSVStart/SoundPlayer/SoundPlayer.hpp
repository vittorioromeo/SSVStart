// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_SOUNDPLAYER
#define SSVS_SOUNDPLAYER

#include <SFML/Audio.hpp>
#include <SSVUtils/MemoryManager/MemoryManager.hpp>

namespace ssvs
{
	class SoundPlayer
	{
		private:
			float volume{100};
			ssvu::MonoManager<sf::Sound> sounds;

			inline void refreshVolume() { for(auto& s : sounds) s->setVolume(volume); }

		public:
			enum class Mode{Overlap, Override, Abort};

			inline auto& play(sf::SoundBuffer& mSoundBuffer, Mode mMode = Mode::Overlap, float mPitch = 1.f)
			{
				for(const auto& s : sounds) if(s->getStatus() == sf::Sound::Status::Stopped) sounds.del(*s);
				sounds.refresh();

				if(mMode == Mode::Override)		{ stop(mSoundBuffer); }
				else if(mMode == Mode::Abort)	{ auto first(findFirst(mSoundBuffer)); if(first != nullptr) return *first; }

				auto& sound(sounds.create(mSoundBuffer));
				sound.setVolume(volume); sound.setPitch(mPitch);
				sound.play();

				return sound;
			}
			inline void stop() { for(auto& s : sounds) s->stop(); }
			inline void stop(const sf::SoundBuffer& mSoundBuffer) { for(auto& s : sounds) if(s->getBuffer() == &mSoundBuffer) s->stop(); }

			inline void setVolume(float mVolume)	{ volume = mVolume; refreshVolume(); }
			inline float getVolume() const noexcept	{ return volume; }

			inline bool isPlaying(const sf::SoundBuffer& mSoundBuffer) const { return findFirst(mSoundBuffer) != nullptr; }
			inline sf::Sound* findFirst(const sf::SoundBuffer& mSoundBuffer) const
			{
				for(const auto& s : sounds) if(s->getBuffer() == &mSoundBuffer) return s.get();
				return nullptr;
			}
	};
}

#endif
