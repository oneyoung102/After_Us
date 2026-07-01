#pragma once

#include <SFML/Graphics.hpp>
#include "tools/pos.hpp"
#include "printText.hpp"
#include <string>
#include "resourceManager/printManager/imageConstant.hpp"

class PrintTextZoom : public PrintText
{
    protected:
        int size;
        const int cycle, dsize, dcycle;
        int cycleCount;
        bool size_bigger;
    public:
        PrintTextZoom(tools::POSf pos, const std::string& content, const sf::Font& font, int size, int cycle,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = imageConstant::PRINT_IMMORTAL);
        virtual void print(sf::RenderWindow& w);
};
