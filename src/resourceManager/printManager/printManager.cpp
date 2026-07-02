#include <SFML/Graphics.hpp>

#include "printManager.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include <vector>

using namespace std;
using namespace sf;


PrintManager::PrintManager()
{
    if(!shader.loadFromFile(FileManager::get_folder_path("Data")/"brightness.txt", sf::Shader::Type::Fragment))
        throw runtime_error("file for shading doesn't exist");
    shader.setUniform("brightness", image_constant::BRIGHTNESS);
}

void PrintManager::print_objects(RenderWindow& window)
{
    for(int i = 0 ; i < __print_objects.size() ; )
        if(__print_objects[i]->is_alive())
        {
            __print_objects[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(__print_objects[i], __print_objects.back());
            __print_objects.pop_back();
        }
}
void PrintManager::print_texts(RenderWindow& window)
{
    for(int i = 0 ; i < __print_texts.size() ; )
        if(__print_texts[i]->is_alive())
        {
            __print_texts[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(__print_texts[i], __print_texts.back());
            __print_texts.pop_back();
        }
}
void PrintManager::print_buttons(RenderWindow& window)
{
    for(int i = 0 ; i < __print_buttons.size() ; )
        if(__print_buttons[i]->is_alive())
        {
            __print_buttons[i]->print(window, shader);
            ++i;
        }
        else
        {
            std::swap(__print_buttons[i], __print_buttons.back());
            __print_buttons.pop_back();
        }
}

void PrintManager::add_object(unique_ptr<PrintObjectInterface>&& object){__print_objects.push_back(std::move(object));}
void PrintManager::add_text(unique_ptr<PrintText>&& text){__print_texts.push_back(std::move(text));}
void PrintManager::add_button(unique_ptr<PrintButton>&& button){__print_buttons.push_back(std::move(button));}

bool PrintManager::object_is_empty(){return __print_objects.empty();}
bool PrintManager::text_is_empty(){return __print_texts.empty();}
bool PrintManager::button_is_empty(){return __print_buttons.empty();}

void PrintManager::clear_object_back(){__print_objects.pop_back();}
void PrintManager::clear_text_back(){__print_texts.pop_back();}
void PrintManager::clear_button_back(){__print_buttons.pop_back();}

bool PrintManager::object_back_is_alive()
{
    return !__print_objects.empty()
        && __print_objects.back()->is_alive()
        && !__print_objects.back()->is_immortal();
}
bool PrintManager::text_back_is_alive()
{
    return !__print_texts.empty()
        && __print_texts.back()->is_alive()
        && !__print_texts.back()->is_immortal();
}
bool PrintManager::button_back_is_alive()
{
    return !__print_buttons.empty()
        && __print_buttons.back()->is_alive()
        && !__print_buttons.back()->is_immortal();
}

