#pragma once

#include <SFML/Graphics.hpp>
#include "tools/pos.hpp"
#include "printText.hpp"
#include "tools/tick.hpp"
#include <string>

class PrintTextFlash : public PrintText
{
    private:
        const tools::Tick cycle;//옵션 주기
        tools::Tick cycle_count;
        bool show;
    public:
        PrintTextFlash(tools::POSf pos, const std::string& content, const sf::Font& font, int size, tools::Tick cycle, 
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, tools::Tick life = IMMORTAL);
        void print(sf::RenderWindow& w) override;
};
