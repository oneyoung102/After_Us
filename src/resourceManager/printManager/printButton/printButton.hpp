#pragma once

#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/pos.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class PrintButton
{
    protected:
        constexpr static int IMMORTAL = -1;
        constexpr static int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
        constexpr static float BUTTON_BRIGHTNESS = 0.15;

        int life;
        const ImageDatas::IMAGE_DATA& image_data;
        sf::Sprite sprite;  
        sf::Text text;
        const bool& selected;
        tools::POSi img_pos;
    public:
        PrintButton(const ImageDatas::IMAGE_DATA& image_data, const bool& selected, tools::POSf pos, const std::string& content, const sf::Font& font,
            float scaling = 1.0, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = IMMORTAL);
        ~PrintButton() = default;
        bool is_alive();
        bool is_immortal();
        virtual void print(sf::RenderWindow& w, Shader& shader);
};
