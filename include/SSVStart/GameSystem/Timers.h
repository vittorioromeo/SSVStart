#ifndef SSVS_TRAITS_WINDOWTIMERTRAITS
#define SSVS_TRAITS_WINDOWTIMERTRAITS

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ssvs
{
	class GameWindow;

	struct TimerBase
	{
		GameWindow& gameWindow;
		sf::Clock clock;
		float frameTime{0}, fps{0};

		TimerBase(GameWindow& mGameWindow);
		virtual ~TimerBase();

		virtual void runUpdate();
		virtual void runDraw();
		virtual void runFrameTime();
		virtual void runFps();

		float getFrameTime() const;
		float getFps() const;
	};

	struct StaticTimer : public TimerBase
	{
		float step{1.f}, accumulatedTime{0}, loops{0}, maxLoops{50}, speedMultiplier{1.f};

		StaticTimer(GameWindow& mGameWindow, float mStep = 1.f, float mSpeedMultiplier = 1.f);
		~StaticTimer();

		void runUpdate() override;
	};

	struct DynamicTimer : public TimerBase
	{
		float frameTimeLimit{4.f};

		DynamicTimer(GameWindow& mGameWindow);
		~DynamicTimer();

		void runUpdate() override;
		void runFps() override;
	};

	StaticTimer& createStaticTimer(GameWindow& mGameWindow, float mStep = 1.f, float mSpeedMultiplier = 1.f);
	DynamicTimer& createDynamicTimer(GameWindow& mGameWindow);
}

#endif
