#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "tools/pos.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class WindowManager
{
    public :
        using ScreenSizeType = tools::POSf;
    private :
        sf::VideoMode videoMode;

        static ScreenSizeType screen_size, screen_center;
        static constexpr float ratio = 16.0f / 9.0f; // 가로 세로 비율 (16:9)
        
        sf::RenderWindow window;
        sf::View view;

        sf::Texture capture_texture;
        sf::Sprite capture_sprite;

        sf::FloatRect get_resized_viewport(const sf::Vector2u& window_size);
        sf::FloatRect get_resized_window(const sf::Event::Resized* resize);
    public :
        WindowManager(std::string&& name);

        static ScreenSizeType get_screen_size();
        static ScreenSizeType get_screen_center();

        static float get_scale(const Camera& camera);
        static tools::POSf get_pixel_world_origin(const Camera& camera);
        static tools::POSs get_pixel_world_size(const Camera& camera);
        static tools::POSf pixel_pos_to_world_pos(const tools::POSf& pixel_pos, const Camera& camera);
        static tools::POSf world_pos_to_pixel_pos(const tools::POSf& world_pos, const Camera& camera);
        static std::pair<tools::POSf,tools::POSf> get_displayed_world_range(const World& world, const Camera& camera);

        const decltype(window)& get_window() const;
        decltype(window)& get_window();

        const sf::View& get_view() const;
        sf::View& get_view();

        void capture_window();
        decltype(capture_sprite) get_capture_sprite() const;

        void clear(sf::Color color = sf::Color::Black);
        void close();
        bool is_open() const;
        void display();

        std::optional<sf::Event> poll_event();

        void resize_window(const std::optional<sf::Event>& event);
        void set_view();
};