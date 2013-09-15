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
			struct ManageableSound : public sf::Sound, public ssvu::MemoryManageable { using sf::Sound::Sound; };

			int volume{100};
			ssvu::MemoryManager<ManageableSound> sounds;

			inline void refreshVolume() { for(auto& s : sounds) s->setVolume(volume); }

		public:
			enum class Mode{Overlap, Override, Abort};

			inline ManageableSound& play(sf::SoundBuffer& mSoundBuffer, Mode mMode = Mode::Overlap, float mPitch = 1.f)
			{
				for(const auto& s : sounds) if(s->getStatus() == sf::Sound::Status::Stopped) sounds.del(*s);
				sounds.refresh();

				switch(mMode)
				{
					case Mode::Overlap: break;
					case Mode::Override: stop(mSoundBuffer); break;
					case Mode::Abort:
						auto first(findFirst(mSoundBuffer));
						if(first != nullptr) return *first;
						break;
				}

				auto& sound(sounds.create(mSoundBuffer));
				sound.setVolume(volume); sound.setPitch(mPitch);
				sound.play();

				return sound;
			}
			inline void stop() { for(auto& s : sounds) s->stop(); }
			inline void stop(const sf::SoundBuffer& mSoundBuffer) { for(auto& s : sounds) if(s->getBuffer() == &mSoundBuffer) s->stop(); }

			inline void setVolume(int mVolume)		{ volume = mVolume; refreshVolume(); }
			inline int getVolume() const noexcept	{ return volume; }

			inline bool isPlaying(const sf::SoundBuffer& mSoundBuffer) const { return findFirst(mSoundBuffer) != nullptr; }
			inline ManageableSound* findFirst(const sf::SoundBuffer& mSoundBuffer) const
			{
				for(const auto& s : sounds) if(s->getBuffer() == &mSoundBuffer) return s.get();
				return nullptr;
			}
	};
}

#endif
