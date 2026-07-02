#pragma once

#include "tools/pos.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class WindowManager
{
    public :
        using ScreenSizeType = tools::POSf;
    private :
        sf::VideoMode videoMode;

        const ScreenSizeType screen_size, screen_center;
        const float ratio;
        
        sf::RenderWindow window;
        sf::View view;

        sf::Texture capture_texture;
        sf::Sprite capture_sprite;

        sf::FloatRect get_resized_window(const sf::Event::Resized* resize);
    public :
        WindowManager(std::string&& name);

        ScreenSizeType get_screen_size();
        ScreenSizeType get_screen_center();

        const decltype(window)& get_window() const;
        decltype(window)& get_window();

        void capture_window();
        decltype(capture_sprite) get_capture_sprite() const;

        void clear(sf::Color color = sf::Color::Black);
        void close();
        bool is_open() const;
        void display();

        void set_frame_rate_limit(unsigned int frame_rate);

        std::optional<sf::Event> poll_event();

        void resize_window(const std::optional<sf::Event>& event);
        void set_view();
};