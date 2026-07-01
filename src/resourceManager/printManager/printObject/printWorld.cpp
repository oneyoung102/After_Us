#include "resourceManager/printManager/printObject/printWorld.hpp"
#include "resourceManager/printManager/imageConstant.hpp"

using namespace imageConstant;

PrintWorld::PrintWorld(const std::vector<std::vector<BlockCode>>& world, const tools::POSf& screenSize, sf::Sprite s)
    : PrintObject(s)
    , world(world)
{
    pos = (screenSize - tools::POSf(world[0].size(),world.size())*BLOCK_SIZE)/2;
}

void PrintWorld::printBlock(sf::RenderWindow& w, const tools::POSf& screen_pos, BlockCode blockCode)
{
    sprite.setTextureRect(sf::IntRect({BLOCK_POS[blockCode].x,BLOCK_POS[blockCode].y}, {BLOCK_SIZE.x, BLOCK_SIZE.y})); 
    printSprite(w,screen_pos);
}

void PrintWorld::print(sf::RenderWindow& w)
{
    for(int y = 0 ; y < world.size() ; y++)
        for(int x = 0 ; x < world[y].size() ; x++)
            printBlock(w,tools::POSf(x,y)*BLOCK_SIZE,world[y][x]);
}