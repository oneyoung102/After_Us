#include "printText.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include "printTextZoom.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

PrintTextZoom::PrintTextZoom(tools::POSf pos, const string& content, const Font& font, int size, int cycle, sf::Color color, sf::Text::Style style, int life)
    : PrintText(pos,content,font,size,color,style,life)
    , cycle(cycle)
    , dsize(max(1,size/imageConstant::TEXT_ZOOM_SIZE_PROP))
    , dcycle(max(1,cycle/imageConstant::TEXT_ZOOM_CYCLE_PROP))
    , cycleCount(0)
    , size_bigger(true)
    , size(size)
{}

void PrintTextZoom::print(RenderWindow& window)
{
    if(++cycleCount >= cycle)
    {
        size_bigger = !size_bigger;
        cycleCount = 0;
    }
    if(cycleCount%dcycle == 0)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f,bounds.position.y + bounds.size.y / 2.f});
        if(size_bigger)
            text.setCharacterSize(size+=dsize);
        else
            text.setCharacterSize(size-=dsize);
    }
    window.draw(text);
    if(isAlive())
        --life;
}
