#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "tools/pos.hpp"

class PrintText
{
    protected:
        constexpr static int IMMORTAL = -1;
        constexpr static int TEXT_ZOOM_SIZE_PROP = 30, TEXT_ZOOM_CYCLE_PROP = 15;
        int life;
        sf::Text text;
    public:
        PrintText(tools::POSf pos, const std::string& content, const sf::Font& font, int size,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = IMMORTAL);
        virtual ~PrintText() = default;
        bool is_alive();
        bool is_immortal();
        virtual void print(sf::RenderWindow& w);
};
