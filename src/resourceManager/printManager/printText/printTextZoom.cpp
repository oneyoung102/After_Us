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
    , d_size(max(1,size/image_constant::TEXT_ZOOM_SIZE_PROP))
    , d_cycle(max(1,cycle/image_constant::TEXT_ZOOM_CYCLE_PROP))
    , cycle_count(0)
    , size_bigger(true)
    , size(size)
{}

void PrintTextZoom::print(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        size_bigger = !size_bigger;
        cycle_count = 0;
    }
    if(cycle_count%d_cycle == 0)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f,bounds.position.y + bounds.size.y / 2.f});
        if(size_bigger)
            text.setCharacterSize(size+=d_size);
        else
            text.setCharacterSize(size-=d_size);
    }
    window.draw(text);
    if(is_alive())
        --life;
}
