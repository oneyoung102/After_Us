#pragma once

#include "tools/pos.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class WindowManager
{
    public :
        using SCREEN_SIZE_TYPE = tools::POSf;
    private :
        sf::VideoMode videoMode;

        const SCREEN_SIZE_TYPE screenSize, screenCenter;
        const float ratio;
        
        sf::RenderWindow window;
        sf::View view;

        sf::Texture captureTexture;
        sf::Sprite captureSprite;

        const sf::Event::Resized* getResizeEvent(const sf::Event& event);
        sf::FloatRect getResizedWindow(const sf::Event::Resized* resize);
    public :
        WindowManager(std::string&& name);

        SCREEN_SIZE_TYPE getScreenSize();
        SCREEN_SIZE_TYPE getScreenCenter();

        const decltype(window)& getWindow() const;
        decltype(window)& getWindow();

        void captureWindow();
        decltype(captureSprite) getCaptureSprite() const;

        void clear(sf::Color color = sf::Color::Black);
        void close();
        bool isOpen() const;
        void display();

        void setFrameRateLimit(unsigned int frameRate);

        std::optional<sf::Event> pollEvent();

        void resizeWindow(const sf::Event& event);
        void setView();
};