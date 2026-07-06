#pragma once

#include "main/windowManager/tick.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/pos.hpp"
#include <SFML/Graphics.hpp>

class PrintObjectInterface
{
    protected:
        const ImageDatas::IMAGE_DATA& image_data;
        sf::Sprite sprite;
        tools::POSf pos;
        Tick life;
        void print_sprite(sf::RenderWindow& window, const tools::POSf& screen_pos, Shader& shader)
        {
            sprite.setPosition(sf::Vector2f(screen_pos.x,screen_pos.y));
            window.draw(sprite, &shader);
            if(is_alive())
                --life;
        }
        void print_transparent(sf::RenderWindow& window, sf::Color&& color, const tools::POSf& screen_pos, tools::POSf&& size)
        {
            sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
            rect.setFillColor(color);
            rect.setPosition(sf::Vector2f(screen_pos.x, screen_pos.y));
            window.draw(rect);
        }
    public:
        static constexpr int IMMORTAL = -1;

        PrintObjectInterface(const ImageDatas::IMAGE_DATA& image_data, const tools::POSf& pos, Tick life = IMMORTAL)
            : image_data(image_data)
            , sprite(image_data.get_sprite())
            , pos(pos)
            , life(life) // life == -1 일 때는 영생
        {}

        PrintObjectInterface(const ImageDatas::IMAGE_DATA& image_data, Tick life = IMMORTAL)
            : image_data(image_data)
            , sprite(image_data.get_sprite())
            , pos()
            , life(life) // life == -1 일 때는 영생
        {}
        virtual ~PrintObjectInterface() = default;

        bool is_alive() const {return life != 0;}
        bool is_immortal() const {return life == IMMORTAL;}

        virtual void print(sf::RenderWindow& w, Shader& shader) = 0;
};


template<class T = void>
class PrintObject : public PrintObjectInterface
{};
