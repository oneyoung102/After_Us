#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"

class PrintText
{
    protected:
        int life;
        sf::Text text;
    public:
        PrintText(tools::POSf pos, const std::string& content, const sf::Font& font, int size,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = imageConstant::PRINT_IMMORTAL);
        virtual ~PrintText() = default;
        bool alive();
        bool is_immortal();
        virtual void print(sf::RenderWindow& w);
};
