#pragma once

#include <SFML/Graphics.hpp>
#include "main/windowManager/tick.hpp"
#include "tools/pos.hpp"
#include "printText.hpp"
#include <string>

class PrintTextZoom : public PrintText
{
    protected:
        int size;
        const int d_size;
        const Tick cycle, d_cycle;
        Tick cycle_count;
        bool size_bigger;
    public:
        PrintTextZoom(tools::POSf pos, const std::string& content, const sf::Font& font, int size, Tick cycle,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, Tick life = IMMORTAL);
        virtual void print(sf::RenderWindow& w) override;
};
