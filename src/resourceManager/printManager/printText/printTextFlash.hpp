#pragma once

#include <SFML/Graphics.hpp>
#include "main/windowManager/tick.hpp"
#include "tools/pos.hpp"
#include "printText.hpp"
#include <string>

class PrintTextFlash : public PrintText
{
    private:
        const Tick cycle;//옵션 주기
        Tick cycle_count;
        bool show;
    public:
        PrintTextFlash(tools::POSf pos, const std::string& content, const sf::Font& font, int size, Tick cycle, 
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, Tick life = IMMORTAL);
        void print(sf::RenderWindow& w) override;
};
