#pragma once

#include <SFML/Graphics.hpp>

class Shader
{
    private :
        sf::Shader shader;
        float brightness;
    public :
        Shader();
        sf::Shader& operator*();

        static float get_brightness_by_height(int curr_tile_height, int tile_height);

        void set_brightness(float brightness = 1.0);
        float get_brightness() const;
};