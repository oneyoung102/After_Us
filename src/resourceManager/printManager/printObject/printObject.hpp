#pragma once

#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <SFML/Graphics.hpp>

class PrintObjectInterface
{
    protected:
        sf::Sprite sprite;
        tools::POSf pos;
        int life;
        void print_sprite(sf::RenderWindow& window, const tools::POSf& screen_pos)
        {
            sprite.setPosition(sf::Vector2f(screen_pos.x,screen_pos.y));
            window.draw(sprite);
            if(is_alive())
                --life;
        }
    public:
        PrintObjectInterface(sf::Sprite s, const tools::POSf& pos, int life = image_constant::PRINT_IMMORTAL)
            : sprite(s)
            , pos(pos)
            , life(life) // life == -1 일 때는 영생
        {}

        PrintObjectInterface(sf::Sprite s, int life = image_constant::PRINT_IMMORTAL)
            : sprite(s)
            , pos()
            , life(life) // life == -1 일 때는 영생
        {}
        virtual ~PrintObjectInterface() = default;

        bool is_alive() const {return life != 0;}
        bool is_immortal() const {return life == image_constant::PRINT_IMMORTAL;}

        virtual void print(sf::RenderWindow& w) = 0;
};


template<class T = void>
class PrintObject : public PrintObjectInterface
{};
