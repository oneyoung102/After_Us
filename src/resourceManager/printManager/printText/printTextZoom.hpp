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
        const int cycle, d_size, d_cycle;
        int cycle_count;
        bool size_bigger;
    public:
        PrintTextZoom(tools::POSf pos, const std::string& content, const sf::Font& font, int size, int cycle,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = image_constant::PRINT_IMMORTAL);
        virtual void print(sf::RenderWindow& w) override;
};
