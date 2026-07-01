#include "printDialButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "resourceManager/printManager/printButton/printButton.hpp"

using namespace std;
using namespace sf;

PrintDialButton::PrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, tools::POSf pos, const string& content, const Font& font, float scaling, sf::Color color, sf::Text::Style style, int life)
    : PrintButton(s,selected,pos,content,font,scaling,color,style,life)
    , dial_selected(dial_selected)
{}
void PrintDialButton::print(RenderWindow& window, const Shader& shader)
{
    if(selected)
    {
        if(dial_selected) 
            window.draw(sprite,&shader);
        else 
            window.draw(sprite);
        window.draw(text);
    }  
    if(alive())
        --life;
}
