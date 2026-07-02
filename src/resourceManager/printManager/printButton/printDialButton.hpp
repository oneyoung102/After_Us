#pragma once

#include "tools/pos.hpp"
#include "resourceManager/printManager/printButton/printButton.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class PrintDialButton : public PrintButton
{
    private :
        const bool& dial_selected;
    public:
        PrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, tools::POSf pos, const std::string& content, const sf::Font& font,
            float scaling = 1.0, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = image_constant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w, const sf::Shader& shader) override;
};
