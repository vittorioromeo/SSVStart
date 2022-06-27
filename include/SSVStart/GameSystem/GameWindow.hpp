// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Input.hpp"
#include "SSVStart/GameSystem/GameEngine.hpp"
#include "SSVStart/GameSystem/GameState.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cassert>

namespace ssvs {

class GameWindow
{
private:
    Input::InputState inputState;
    std::unique_ptr<GameEngine> gameEngine{
        std::make_unique<GameEngine>()}; // TODO: should the user create a
                                         // GameEngine?
    sf::RenderWindow renderWindow;
    std::string title;
    ssvu::FT msUpdate, msDraw;
    float maxFPS{60.f}, pixelMult{1.f};
    unsigned int width{640}, height{480}, antialiasingLevel{3};
    bool fpsLimited{false}, focus{true}, mustRecreate{true}, vsync{false},
        fullscreen{false};

    void runEvents()
    {
        assert(gameEngine != nullptr);

        sf::Event event;
        while(renderWindow.pollEvent(event))
        {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
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
#pragma GCC diagnostic pop
    }

    void recreateWindow()
    {
        if(renderWindow.isOpen()) renderWindow.close();

        renderWindow.create(sf::VideoMode{{width, height}}, title,
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

    GameWindow()
    {
        gameEngine->setInputState(inputState);
    }

    GameWindow(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&) = delete;

    GameWindow(GameWindow&&) = delete;
    GameWindow& operator=(GameWindow&&) = delete;

    void run()
    {
        assert(gameEngine != nullptr);

        while(gameEngine->isRunning())
        {
            if(mustRecreate) recreateWindow();

            renderWindow.setActive(true);
            this->clear();

            gameEngine->refreshTimer();

            auto tempMs(std::chrono::high_resolution_clock::now());
            {
                runEvents();
                gameEngine->runUpdate();
            }
            msUpdate = std::chrono::duration_cast<ssvu::FTDuration>(
                std::chrono::high_resolution_clock::now() - tempMs)
                           .count();

            tempMs = std::chrono::high_resolution_clock::now();
            {
                gameEngine->runDraw();
                renderWindow.display();
            }
            msDraw = std::chrono::duration_cast<ssvu::FTDuration>(
                std::chrono::high_resolution_clock::now() - tempMs)
                         .count();

            gameEngine->runFPS();
        }
    }
    void stop() noexcept
    {
        assert(gameEngine != nullptr);
        gameEngine->stop();
    }

    void clear(const sf::Color& mColor = sf::Color::Transparent)
    {
        renderWindow.clear(mColor);
    }
    void draw(const sf::Drawable& mDrawable,
        const sf::RenderStates& mStates = sf::RenderStates::Default)
    {
        renderWindow.draw(mDrawable, mStates);
    }

    void saveScreenshot(const std::string& mPath) const
    {
        sf::Texture t;
        t.create({renderWindow.getSize().x, renderWindow.getSize().y});
        t.update(renderWindow);
        auto img = t.copyToImage();
        img.saveToFile(mPath);
    }

    void setFullscreen(bool mFullscreen) noexcept
    {
        fullscreen = mFullscreen;
        mustRecreate = true;
    }
    void setSize(unsigned int mWidth, unsigned int mHeight) noexcept
    {
        width = mWidth;
        height = mHeight;
        mustRecreate = true;
    }
    void setAntialiasingLevel(unsigned int mLevel) noexcept
    {
        antialiasingLevel = mLevel;
        mustRecreate = true;
    }
    void setVsync(bool mEnabled) noexcept
    {
        vsync = mEnabled;
        mustRecreate = true;
    }
    void setPixelMult(float mPixelMult) noexcept
    {
        pixelMult = mPixelMult;
        mustRecreate = true;
    }

    void setMouseCursorVisible(bool mEnabled)
    {
        renderWindow.setMouseCursorVisible(mEnabled);
    }
    void setTitle(std::string mTitle)
    {
        title = std::move(mTitle);
        renderWindow.setTitle(mTitle);
    }
    void setMaxFPS(float mMaxFPS)
    {
        maxFPS = mMaxFPS;
        renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    void setFPSLimited(bool mFPSLimited)
    {
        fpsLimited = mFPSLimited;
        renderWindow.setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    void setGameState(GameState& mGameState) noexcept
    {
        assert(gameEngine != nullptr);
        gameEngine->setGameState(mGameState);
    }

    void setView(const sf::View& view)
    {
        renderWindow.setView(view);
    }

    operator sf::RenderWindow&() noexcept
    {
        return renderWindow;
    }
    auto& getRenderWindow() noexcept
    {
        return renderWindow;
    }
    const auto& getRenderWindow() const noexcept
    {
        return renderWindow;
    }
    bool getFullscreen() const noexcept
    {
        return fullscreen;
    }
    auto getWidth() const noexcept
    {
        return width;
    }
    auto getHeight() const noexcept
    {
        return height;
    }
    auto getAntialiasingLevel() const noexcept
    {
        return antialiasingLevel;
    }
    bool hasFocus() const noexcept
    {
        return focus;
    }
    bool getVsync() const noexcept
    {
        return vsync;
    }

    ssvu::FT getMsUpdate() const noexcept
    {
        return msUpdate;
    }
    ssvu::FT getMsDraw() const noexcept
    {
        return msDraw;
    }

    auto getMousePosition() const noexcept
    {
        return renderWindow.mapPixelToCoords(
            sf::Mouse::getPosition(renderWindow));
    }
    auto getFingerPosition(FingerID mX) const noexcept
    {
        return renderWindow.mapPixelToCoords(
            sf::Touch::getPosition(mX, renderWindow));
    }

    const auto& getInputState() const noexcept
    {
        return inputState;
    }

    auto getFingerDownCount() const noexcept
    {
        return inputState.fingers.count();
    }
    auto getFingerDownPositions() const noexcept
    {
        std::vector<Vec2i> result;

        // TODO: bitset iteration function (forTrueBits?)
        for(auto i(0u); i < fingerCount; ++i)
            if(inputState.fingers[i]) result.emplace_back(getFingerPosition(i));

        return result;
    }

    template <typename T, typename... TArgs>
    void setTimer(TArgs&&... mArgs)
    {
        assert(gameEngine != nullptr);
        gameEngine->setTimer<T, TArgs...>(FWD(mArgs)...);
    }

    [[nodiscard]] TimerBase& getTimerBase() noexcept
    {
        assert(gameEngine != nullptr);
        return gameEngine->getTimerBase();
    }

    [[nodiscard]] const TimerBase& getTimerBase() const noexcept
    {
        assert(gameEngine != nullptr);
        return gameEngine->getTimerBase();
    }

    [[nodiscard]] bool hasTimer() const noexcept
    {
        assert(gameEngine != nullptr);
        return gameEngine->hasTimer();
    }

    auto getFPS() const noexcept
    {
        assert(gameEngine != nullptr);
        return gameEngine->getFPS();
    }

    void recreate() noexcept
    {
        mustRecreate = true;
    }
};

} // namespace ssvs
