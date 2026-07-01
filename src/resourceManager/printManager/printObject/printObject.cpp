#include "resourceManager/printManager/printObject/printObject.hpp"
#include <SFML/Graphics.hpp>
#include "resourceManager/printManager/imageConstant.hpp"
#include "tools/pos.hpp"

using namespace imageConstant;
using namespace tools;
using namespace sf;

PrintObject::PrintObject(Sprite s, const POSf& pos, int life)
    : sprite(s)
    , pos(pos)
    , life(life) // life == -1 일 때는 영생
{}

PrintObject::PrintObject(Sprite s, int life)
    : sprite(s)
    , pos()
    , life(life) // life == -1 일 때는 영생
{}

bool PrintObject::isAlive() const {return life != 0;}
bool PrintObject::isImmortal() const {return life == PRINT_IMMORTAL;}

void PrintObject::printSprite(RenderWindow& window, const POSf& screen_pos)
{
    sprite.setPosition(Vector2f(screen_pos.x,screen_pos.y));
    window.draw(sprite);
    if(isAlive())
        --life;
}
void PrintObject::print(RenderWindow& w)
{
    printSprite(w,pos);
}
