#include "printDialButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "resourceManager/printManager/printButton/printButton.hpp"

using namespace std;

PrintDialButton::PrintDialButton(const ImageDatas::IMAGE_DATA& image_data, const bool& selected, const bool& dial_selected, tools::POSf pos, const string& content, const sf::Font& font, float scaling, sf::Color color, sf::Text::Style style, int life)
    : PrintButton(image_data,selected,pos,content,font,scaling,color,style,life)
    , dial_selected(dial_selected)
{}
void PrintDialButton::print(sf::RenderWindow& window, Shader& shader)
{
    if(selected)
    {
        if(dial_selected) 
        {
            shader.set_brightness(BUTTON_BRIGHTNESS);
            window.draw(sprite,&*shader);
            }
        else 
            window.draw(sprite);
        window.draw(text);
    }  
    if(is_alive())
        --life;
}
