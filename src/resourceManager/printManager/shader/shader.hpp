#pragma once

#include <SFML/Graphics.hpp>

class Shader
{
    private :
        static constexpr float SHADABLE_HEIGHT = 5.f;
        static constexpr float SHADE_LEVEL = 0.1;
        sf::Shader shader;
        float brightness;
    public :
        Shader();
        sf::Shader& operator*() noexcept { return shader; }
        const sf::Shader& operator*() const noexcept { return shader; }

        sf::Shader* operator&() noexcept { return &shader; }
        const sf::Shader* operator&() const noexcept { return &shader; }

        operator sf::Shader&() noexcept { return shader; }
        operator const sf::Shader&() const noexcept { return shader; }

        operator sf::RenderStates() const noexcept { return sf::RenderStates(&shader); }

        static float get_brightness_by_height(int curr_tile_height, int tile_height);

        void set_brightness(float brightness = 1.0);
        float get_brightness() const;
};