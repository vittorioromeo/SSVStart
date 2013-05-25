#ifndef SSVS_GAMEWINDOW_TIMERS_STATIC
#define SSVS_GAMEWINDOW_TIMERS_STATIC

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SSVStart/GameSystem/Timers/TimerBase.h"

namespace ssvs
{
	class GameWindow;

	struct StaticTimer : public TimerBase
	{
		float step, timeSlice, maxLoops, time{0}, loops{0};

		StaticTimer(GameWindow& mGameWindow, float mStep = 1.f, float mTimeSlice = 1.f, float mMaxLoops = 50);
		~StaticTimer();

		void runUpdate() override;

		// Getters
		float getStep() const;
		float getTimeSlice() const;
		float getMaxLoops() const;
		float getTime() const;
		float getLoops() const;

		// Setters
		void setStep(float mStep);
		void setTimeSlice(float mTimeSlice);
		void setMaxLoops(float mMaxLoops);
	};

	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep = 1.f, float mSpeed = 1.f, float mMaxLoops = 50);
}

#endif
