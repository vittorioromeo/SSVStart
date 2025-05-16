// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#pragma once

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Input.hpp"
#include "SSVStart/GameSystem/GameEngine.hpp"
#include "SSVStart/GameSystem/GameState.hpp"
#include "SSVUtils/Core/Common/Aliases.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/ImageUtxils.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/System/String.hpp>
#include <SFML/System/Path.hpp>

#include <SFML/Base/Optional.hpp>

#include <chrono>
#include <vector>

#include <cassert>

namespace ssvs {

class GameWindow
{
private:
    Input::InputState inputState;
    std::unique_ptr<GameEngine> gameEngine{
        std::make_unique<GameEngine>()}; // TODO: should the user create a
                                         // GameEngine?
    sf::base::Optional<sf::RenderWindow> renderWindow;
    std::string title;
    float msUpdate, msDraw;
    float maxFPS{60.f}, pixelMult{1.f};
    unsigned int width{640}, height{480}, antialiasingLevel{3};
    bool fpsLimited{false}, focus{true}, mustRecreate{true}, vsync{false},
        fullscreen{false};

    void runEvents()
    {
        assert(gameEngine != nullptr);

        while(const auto optEvent = renderWindow->pollEvent())
        {
            auto& event = optEvent.value();

            if(event.is<sf::Event::Closed>())
            {
                gameEngine->stop();
            }
            else if(event.is<sf::Event::FocusGained>())
            {
                focus = true;
            }
            else if(event.is<sf::Event::FocusLost>())
            {
                inputState.reset();
                focus = false;
            }
            else if(auto* e = event.getIf<sf::Event::KeyPressed>())
            {
                inputState[e->code] = true;
            }
            else if(auto* e = event.getIf<sf::Event::KeyReleased>())
            {
                inputState[e->code] = false;
            }
            else if(auto* e = event.getIf<sf::Event::MouseButtonPressed>())
            {
                inputState[e->button] = true;
            }
            else if(auto* e = event.getIf<sf::Event::MouseButtonReleased>())
            {
                inputState[e->button] = false;
            }
            else if(auto* e = event.getIf<sf::Event::TouchBegan>())
            {
                inputState.getFinger(e->finger) = true;
            }
            else if(auto* e = event.getIf<sf::Event::TouchEnded>())
            {
                inputState.getFinger(e->finger) = false;
            }

            gameEngine->handleEvent(event);
        }
    }

    void recreateWindow()
    {
        renderWindow.reset();

        sf::WindowSettings settings{
            .size = {width, height},
            .title = title,
            .fullscreen = fullscreen,
            .contextSettings = {0, 0, antialiasingLevel, 1, 1},
        };

        renderWindow.emplace(settings);

        renderWindow->setSize(sf::Vec2u(width * pixelMult, height * pixelMult));
        renderWindow->setVerticalSyncEnabled(vsync);
        renderWindow->setFramerateLimit(fpsLimited ? maxFPS : 0);

        inputState.reset();

        mustRecreate = false;
        onRecreation();
    }

public:
    ssvu::Delegate<void()> onRecreation;

    GameWindow()
    {
        recreateWindow();
        gameEngine->setInputState(inputState);
    }

    GameWindow(const GameWindow&) = delete;
    GameWindow& operator=(const GameWindow&) = delete;

    GameWindow(GameWindow&&) = delete;
    GameWindow& operator=(GameWindow&&) = delete;

    void run()
    {
        using FTDuration = std::chrono::duration<float, std::milli>;

        assert(gameEngine != nullptr);

        while(gameEngine->isRunning())
        {
            if(mustRecreate) recreateWindow();

            (void)renderWindow->setActive(true);
            this->clear();

            gameEngine->refreshTimer();

            auto tempMs(std::chrono::high_resolution_clock::now());
            {
                runEvents();
                gameEngine->runUpdate();
            }
            msUpdate = std::chrono::duration_cast<FTDuration>(
                std::chrono::high_resolution_clock::now() - tempMs)
                           .count();

            tempMs = std::chrono::high_resolution_clock::now();
            {
                gameEngine->runDraw();
                renderWindow->display();
            }
            msDraw = std::chrono::duration_cast<FTDuration>(
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
        renderWindow->clear(mColor);
    }

    template <typename... Ts>
    void draw(Ts&&... xs)
    {
        renderWindow->draw(FWD(xs)...);
    }

    void saveScreenshot(const std::string& mPath) const
    {
        auto t = sf::Texture::create(
            {renderWindow->getSize().x, renderWindow->getSize().y});

        if(!t.hasValue())
        {
            return;
        }

        t->update(*renderWindow);
        auto img = t->copyToImage();

        (void)img.saveToFile(mPath);
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
        renderWindow->setMouseCursorVisible(mEnabled);
    }
    void setTitle(std::string mTitle)
    {
        title = std::move(mTitle);
        renderWindow->setTitle(mTitle);
    }
    void setMaxFPS(float mMaxFPS)
    {
        maxFPS = mMaxFPS;
        renderWindow->setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    void setFPSLimited(bool mFPSLimited)
    {
        fpsLimited = mFPSLimited;
        renderWindow->setFramerateLimit(fpsLimited ? maxFPS : 0);
    }
    void setGameState(GameState& mGameState) noexcept
    {
        assert(gameEngine != nullptr);
        gameEngine->setGameState(mGameState);
    }

    void setView(const sf::View& view)
    {
        renderWindow->setView(view);
    }

    operator sf::RenderWindow&() noexcept
    {
        return *renderWindow;
    }
    auto& getRenderWindow() noexcept
    {
        return *renderWindow;
    }
    const auto& getRenderWindow() const noexcept
    {
        return *renderWindow;
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

    float getMsUpdate() const noexcept
    {
        return msUpdate;
    }
    float getMsDraw() const noexcept
    {
        return msDraw;
    }

    auto getMousePosition() const noexcept
    {
        return renderWindow->mapPixelToCoords(
            sf::Mouse::getPosition(*renderWindow));
    }
    auto getFingerPosition(FingerID mX) const noexcept
    {
        return renderWindow->mapPixelToCoords(
            sf::Touch::getPosition(mX, *renderWindow));
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
        std::vector<sf::Vec2i> result;

        // TODO: bitset iteration function (forTrueBits?)
        for(auto i(0u); i < fingerCount; ++i)
            if(inputState.fingers[i])
                result.emplace_back(getFingerPosition(i).to<sf::Vec2i>());

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
