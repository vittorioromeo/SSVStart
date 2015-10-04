// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_GAMESYSTEM_GAMEWINDOW
#define SSVS_GAMESYSTEM_GAMEWINDOW

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Input.hpp"

namespace ssvs
{
class GameWindow
{
private:
    Input::InputState inputState;
    ssvu::UPtr<GameEngine> gameEngine{
    ssvu::mkUPtr<GameEngine>()}; // TODO: should the user create a GameEngine?
    sf::RenderWindow renderWindow;
    std::string title;
    FT msUpdate, msDraw;
    float maxFPS{60.f}, pixelMult{1.f};
    unsigned int width{640}, height{480}, antialiasingLevel{3};
    bool fpsLimited{false}, focus{true}, mustRecreate{true}, vsync{false},
    fullscreen{false};

    inline void runEvents()
    {
        SSVU_ASSERT(gameEngine != nullptr);

        sf::Event event;
        while(renderWindow.pollEvent(event)) {
            switch(event.type)
            {
                case sf::Event::Closed: gameEngine->stop(); break;
                case sf::Event::GainedFocus: focus = true; break;
                case sf::Event::LostFocus:
                    inputState.reset();
                    focus = false;
                    break;
                case sf::Event::KeyPressed:
                    inputState[event.key.code] = true;
                    break;
                case sf::Event::KeyReleased:
                    inputState[event.key.code] = false;
                    break;
                case sf::Event::MouseButtonPressed:
                    inputState[event.mouseButton.button] = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    inputState[event.mouseButton.button] = false;
                    break;
                case sf::Event::TouchBegan:
                    inputState.getFinger(event.touch.finger) = true;
                    break;
                case sf::Event::TouchEnded:
                    inputState.getFinger(event.touch.finger) = false;
                    break;
                default: break;
            }

            gameEngine->handleEvent(event);
        }
    }

    inline void recreateWindow()
    {
        if(renderWindow.isOpen()) renderWindow.close();

        renderWindow.create({width, height}, title,
        fullscreen ? sf::Style::Fullscreen : sf::Style::Default,
        sf::ContextSettings{0, 0, antialiasingLevel, 0, 0});
        renderWindow.setSize(Vec2u(width * pixelMult, height * pixelMult));
        renderWindow.setVerticalSyncEnabled(vsync);
        renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0);

        inputState.reset();

        mustRecreate = false;
        onRecreation();
    }

public:
    ssvu::Delegate<void()> onRecreation;

    inline GameWindow() { gameEngine->setInputState(inputState); }

    inline GameWindow(const GameWindow&) = delete;
    inline GameWindow& operator=(const GameWindow&) = delete;

    inline GameWindow(GameWindow&&) = default;
    inline GameWindow& operator=(GameWindow&&) = default;

    inline void run()
    {
        SSVU_ASSERT(gameEngine != nullptr);

        while(gameEngine->isRunning()) {
            if(mustRecreate) recreateWindow();

            renderWindow.setActive(true);
            this->clear();

            gameEngine->refreshTimer();

            auto tempMs(HRClock::now());
            {
                runEvents();
                gameEngine->runUpdate();
            }
            msUpdate =
            std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs)
            .count();

            tempMs = HRClock::now();
            {
                gameEngine->runDraw();
                renderWindow.display();
            }
            msDraw =
            std::chrono::duration_cast<FTDuration>(HRClock::now() - tempMs)
            .count();

            gameEngine->runFPS();
        }
    }
    inline void stop() noexcept
    {
        SSVU_ASSERT(gameEngine != nullptr);
        gameEngine->stop();
    }

    inline void clear(const sf::Color& mColor = sf::Color::Transparent)
    {
        renderWindow.clear(mColor);
    }
    inline void draw(const sf::Drawable& mDrawable,
    const sf::RenderStates& mStates = sf::RenderStates::Default)
    {
        renderWindow.draw(mDrawable, mStates);
    }

    inline void saveScreenshot(const ssvufs::Path& mPath) const
    {
        renderWindow.capture().saveToFile(mPath);
    }

    inline void setFullscreen(bool mFullscreen) noexcept
    {
        fullscreen = mFullscreen;
        mustRecreate = true;
    }
    inline void setSize(unsigned int mWidth, unsigned int mHeight) noexcept
    {
        width = mWidth;
        height = mHeight;
        mustRecreate = true;
    }
    inline void setAntialiasingLevel(unsigned int mLevel) noexcept
    {
        antialiasingLevel = mLevel;
        mustRecreate = true;
    }
    inline void setVsync(bool mEnabled) noexcept
    {
        vsync = mEnabled;
        mustRecreate = true;
    }
    inline void setPixelMult(float mPixelMult) noexcept
    {
        pixelMult = mPixelMult;
        mustRecreate = true;
    }

    inline void setMouseCursorVisible(bool mEnabled)
    {
        renderWindow.setMouseCursorVisible(mEnabled);
    }
    inline void setTitle(std::string mTitle)
    {
        title = ssvu::mv(mTitle);
        renderWindow.setTitle(mTitle);
    }
    inline void setMaxFPS(float mMaxFPS)
    {
        maxFPS = mMaxFPS;
        renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    inline void setFPSLimited(bool mFPSLimited)
    {
        fpsLimited = mFPSLimited;
        renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    inline void setGameState(GameState& mGameState) noexcept
    {
        gameEngine->setGameState(mGameState);
    }

    inline operator sf::RenderWindow&() noexcept { return renderWindow; }
    inline auto& getRenderWindow() noexcept { return renderWindow; }
    inline bool getFullscreen() const noexcept { return fullscreen; }
    inline auto getWidth() const noexcept { return width; }
    inline auto getHeight() const noexcept { return height; }
    inline auto getAntialiasingLevel() const noexcept
    {
        return antialiasingLevel;
    }
    inline bool hasFocus() const noexcept { return focus; }
    inline bool getVsync() const noexcept { return vsync; }

    inline FT getMsUpdate() const noexcept { return msUpdate; }
    inline FT getMsDraw() const noexcept { return msDraw; }

    inline auto getMousePosition() const noexcept
    {
        return renderWindow.mapPixelToCoords(
        sf::Mouse::getPosition(renderWindow));
    }
    inline auto getFingerPosition(FingerID mX) const noexcept
    {
        return renderWindow.mapPixelToCoords(
        sf::Touch::getPosition(mX, renderWindow));
    }

    inline const auto& getInputState() const noexcept { return inputState; }

    inline auto getFingerDownCount() const noexcept
    {
        return inputState.fingers.count();
    }
    inline auto getFingerDownPositions() const noexcept
    {
        std::vector<Vec2i> result;

        // TODO: bitset iteration function (forTrueBits?)
        for(auto i(0u); i < fingerCount; ++i)
            if(inputState.fingers[i]) result.emplace_back(getFingerPosition(i));

        return result;
    }

    template <typename T, typename... TArgs>
    inline void setTimer(TArgs&&... mArgs)
    {
        gameEngine->setTimer<T, TArgs...>(FWD(mArgs)...);
    }
    inline auto getFPS() const noexcept { return gameEngine->getFPS(); }

    inline void recreate() noexcept { mustRecreate = true; }
};
}

#endif
