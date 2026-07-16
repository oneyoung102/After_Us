#pragma once

#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include "resourceManager/printManager/shader/shader.hpp"
#include "tools/pos.hpp"
#include <SFML/Graphics.hpp>

class PrintObjectInterface
{
    protected:
        const ImageDatas& image_datas;
        tools::POSf pos;
        tools::Tick life;
        void print_sprite(sf::RenderWindow& window, sf::Sprite sprite, const tools::POSf& screen_pos, Shader& shader)
        {
            sprite.setPosition(sf::Vector2f(screen_pos.x,screen_pos.y));
            window.draw(sprite, &shader);
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

        PrintObjectInterface(const ImageDatas& image_datas, const tools::POSf& pos, tools::Tick life = IMMORTAL)
            : image_datas(image_datas)
            , pos(pos)
            , life(life) // life == -1 일 때는 영생
        {}

        PrintObjectInterface(const ImageDatas& image_datas, tools::Tick life = IMMORTAL)
            : image_datas(image_datas)
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
