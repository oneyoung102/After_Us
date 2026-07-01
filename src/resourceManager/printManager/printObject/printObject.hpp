#pragma once

#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <SFML/Graphics.hpp>

class PrintObject
{
    protected:
        sf::Sprite sprite;
        tools::POSf pos;
        int life;
        void printSprite(sf::RenderWindow& w, const tools::POSf& screen_pos);
    public:
        PrintObject(sf::Sprite s, const tools::POSf& pos, int life = imageConstant::PRINT_IMMORTAL);
        PrintObject(sf::Sprite s, int life = imageConstant::PRINT_IMMORTAL);
        virtual ~PrintObject() = default;
        bool isAlive() const;
        bool isImmortal() const;
        virtual void print(sf::RenderWindow& w);
};
