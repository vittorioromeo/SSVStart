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
			bool enabled{true};
			float current{0.f}, total{0.f}, target;
			unsigned int ticks{0};

			inline void setEnabled(bool mEnabled)	{ enabled = mEnabled; }
			inline void setTarget(float mTarget)	{ target = mTarget; }
			inline bool hasReachedTarget() const	{ return current >= target; }

		public:
			Ticker(float mTarget, bool mEnabled = true) : target{mTarget}, enabled{mEnabled} { }

			inline bool update(float mFrameTime)
			{
				if(!enabled) return false;

				current += mFrameTime;
				total += mFrameTime;

				if(!hasReachedTarget()) return false;

				resetCurrent(); ++ticks;
				return true;
			}
			inline bool update(float mFrameTime, float mTarget) { setTarget(mTarget); return update(mFrameTime); }

			inline void resume() noexcept				{ setEnabled(true); }
			inline void restart() noexcept				{ resetCurrent(); setEnabled(true); }
			inline void restart(float mTarget) noexcept	{ resetCurrent(); setTarget(mTarget); setEnabled(true); }
			inline void pause() noexcept				{ setEnabled(false); }
			inline void stop() noexcept					{ resetCurrent(); setEnabled(false); }

			inline void resetCurrent() noexcept			{ current = 0.f; }
			inline void resetTicks() noexcept			{ ticks = 0; }
			inline void resetTotal() noexcept			{ total = 0.f; }
			inline void resetAll() noexcept				{ resetCurrent(); resetTicks(); resetTotal(); }

			inline bool isRunning() const noexcept			{ return enabled; }
			inline bool isStopped() const noexcept			{ return !enabled; }
			inline float getTarget() const noexcept			{ return target; }
			inline float getCurrent() const noexcept		{ return current; }
			inline float getTotal() const noexcept			{ return total; }
			inline unsigned int getTicks() const noexcept	{ return ticks; }

			template<typename T = float> inline T getTotalSecs() const noexcept		{ return static_cast<T>(framesToSecs(total)); }
			template<typename T = float> inline T getCurrentSecs() const noexcept	{ return static_cast<T>(framesToSecs(current)); }
	};
}

#endif
