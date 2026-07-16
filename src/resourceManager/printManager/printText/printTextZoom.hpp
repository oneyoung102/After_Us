#pragma once

#include <SFML/Graphics.hpp>
#include "tools/pos.hpp"
#include "printText.hpp"
#include "tools/tick.hpp"
#include <string>

class PrintTextZoom : public PrintText
{
    protected:
        int size;
        const int d_size;
        const tools::Tick cycle, d_cycle;
        tools::Tick cycle_count;
        bool size_bigger;
    public:
        PrintTextZoom(tools::POSf pos, const std::string& content, const sf::Font& font, int size, tools::Tick cycle,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, tools::Tick life = IMMORTAL);
        virtual void print(sf::RenderWindow& w) override;
};
