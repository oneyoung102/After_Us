#pragma once

#include "resourceManager/printManager/printObject/printObject.hpp"
#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <SFML/Graphics.hpp>

class PrintWorld : public PrintObject
{
    protected:
        const std::vector<std::vector<imageConstant::BlockCode>>& world;
        void printBlock(sf::RenderWindow& w, const tools::POSf& screen_pos, imageConstant::BlockCode blockCode);
    public:
        PrintWorld(const std::vector<std::vector<imageConstant::BlockCode>>& world, const tools::POSf& screenSize, sf::Sprite s);
        virtual ~PrintWorld() = default;
        virtual void print(sf::RenderWindow& w) override;
};