// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_TICKER
#define SSVS_TICKER

namespace ssvs
{
	template<typename T> constexpr inline static T framesToSecs(T mFrames) noexcept	{ return mFrames / 60.f; }
	template<typename T> constexpr inline static T secsToFrames(T mSecs) noexcept	{ return mSecs * 60.f; }

	class Ticker
	{
		private:
			float target;
			bool running{true}, loop{true};
			float current{0.f}, total{0.f};
			unsigned int ticks{0};

			inline bool hasReachedTarget() const noexcept { return current >= target; }

		public:
			inline Ticker(float mTarget, bool mRunning = true) noexcept : target{mTarget}, running{mRunning} { }

			inline bool update(float mFT) noexcept
			{
				current += mFT * running;
				total += mFT * running;

				if(!hasReachedTarget()) return false;

				++ticks;
				resetCurrent();
				running = loop;
				return true;
			}
			inline bool update(float mFT, float mTarget) noexcept { target = mTarget; return update(mFT); }

			inline void pause() noexcept				{ running = false; }
			inline void resume() noexcept				{ running = true; }
			inline void stop() noexcept					{ resetCurrent(); running = false; }
			inline void restart() noexcept				{ resetCurrent(); running = true; }
			inline void restart(float mTarget) noexcept	{ resetCurrent(); target = mTarget; running = true; }

			inline void resetCurrent() noexcept			{ current = 0.f; }
			inline void resetTicks() noexcept			{ ticks = 0; }
			inline void resetTotal() noexcept			{ total = 0.f; }
			inline void resetAll() noexcept				{ resetCurrent(); resetTicks(); resetTotal(); }

			inline void setLoop(bool mLoop) noexcept		{ loop = mLoop; }

			inline bool getLoop() const noexcept			{ return loop; }
			inline bool isRunning() const noexcept			{ return running; }
			inline float getTarget() const noexcept			{ return target; }
			inline float getCurrent() const noexcept		{ return current; }
			inline float getTotal() const noexcept			{ return total; }
			inline unsigned int getTicks() const noexcept	{ return ticks; }

			template<typename T = float> inline T getTotalSecs() const noexcept		{ return static_cast<T>(framesToSecs(total)); }
			template<typename T = float> inline T getCurrentSecs() const noexcept	{ return static_cast<T>(framesToSecs(current)); }
	};
}

#endif
