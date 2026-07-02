#pragma once

#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class PrintButton
{
    protected:
        int life;
        sf::Sprite sprite;
        sf::Text text;
        const bool& selected;
        tools::POSi img_pos;
    public:
        PrintButton(sf::Sprite s, const bool& selected, tools::POSf pos, const std::string& content, const sf::Font& font,
            float scaling = 1.0, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = image_constant::PRINT_IMMORTAL);
        ~PrintButton() = default;
        bool is_alive();
        bool is_immortal();
        virtual void print(sf::RenderWindow& w, const sf::Shader& shader);
};
