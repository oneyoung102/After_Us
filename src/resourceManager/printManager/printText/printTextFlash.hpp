#pragma once

#include <SFML/Graphics.hpp>
#include "tools/pos.hpp"
#include "printText.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <string>

class PrintTextFlash : public PrintText
{
    private:
        const int cycle;//옵션 주기
        int cycle_count;
        bool show;
    public:
        PrintTextFlash(tools::POSf pos, const std::string& content, const sf::Font& font, int size, int cycle, 
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = imageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};
