#include "printTextFlash.hpp"
#include "printText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

PrintTextFlash::PrintTextFlash(tools::POSf pos, const string& content, const Font& font, int size, Tick cycle, sf::Color color, sf::Text::Style style, Tick life)
    : PrintText(pos,content,font,size,color,style,life)
    , cycle(cycle)
    , cycle_count(0)
    , show(true)
{}

void PrintTextFlash::print(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        show = !show;
        cycle_count = 0;
    }
    if(show)
        window.draw(text);
    if(is_alive())
        --life;
}
