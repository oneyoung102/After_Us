#include "printTextFlash.hpp"
#include "printText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

PrintTextFlash::PrintTextFlash(tools::POSf pos, const string& content, const Font& font, int size, int cycle, sf::Color color, sf::Text::Style style, int life)
    : PrintText(pos,content,font,size,color,style,life)
    , cycle(cycle)
    , cycleCount(0)
    , show(true)
{}

void PrintTextFlash::print(RenderWindow& window)
{
    if(++cycleCount >= cycle)
    {
        show = !show;
        cycleCount = 0;
    }
    if(show)
        window.draw(text);
    if(isAlive())
        --life;
}
