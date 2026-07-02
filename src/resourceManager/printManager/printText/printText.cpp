#include "printText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

PrintText::PrintText(tools::POSf pos, const string& content, const Font& font, int size, Color color, Text::Style style, int life)
    : text(Text(font))
    , life(life)
{
    text.setString(content);
    text.setFillColor(color);
    text.setStyle(style);
    text.setCharacterSize(size);

    // 중심 정렬을 위해 origin을 텍스트 중앙으로 설정
    auto bounds = text.getLocalBounds();
    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
    text.setPosition({pos.x,pos.y});
}

bool PrintText::is_alive(){return life != 0;}
bool PrintText::is_immortal(){return life == image_constant::PRINT_IMMORTAL;}

void PrintText::print(RenderWindow& window)
{
    window.draw(text);
    if(is_alive())
        --life;
}
