#include <SFML/Graphics.hpp>

#include "printManager.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include <vector>

using namespace std;
using namespace sf;


PrintManager::PrintManager()
{
    if(!shader.loadFromFile(FileManager::getFolderPath("Data")/"brightness.txt", sf::Shader::Type::Fragment))
        throw runtime_error("file for shading doesn't exist");
    shader.setUniform("brightness", imageConstant::BRIGHTNESS);
}

void PrintManager::print_all_objects(RenderWindow& window)
{
    for(int i = 0 ; i < printObjects.size() ; )
        if(printObjects[i]->isAlive())
        {
            printObjects[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(printObjects[i], printObjects.back());
            printObjects.pop_back();
        }
}
void PrintManager::print_all_texts(RenderWindow& window)
{
    for(int i = 0 ; i < printTexts.size() ; )
        if(printTexts[i]->alive())
        {
            printTexts[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(printTexts[i], printTexts.back());
            printTexts.pop_back();
        }
}
void PrintManager::print_all_buttons(RenderWindow& window)
{
    for(int i = 0 ; i < printButtons.size() ; )
        if(printButtons[i]->alive())
        {
            printButtons[i]->print(window, shader);
            ++i;
        }
        else
        {
            std::swap(printButtons[i], printButtons.back());
            printButtons.pop_back();
        }
}

void PrintManager::add_print_object(unique_ptr<PrintObject>&& object){printObjects.push_back(std::move(object));}
void PrintManager::add_print_text(unique_ptr<PrintText>&& text){printTexts.push_back(std::move(text));}
void PrintManager::add_print_button(unique_ptr<PrintButton>&& button){printButtons.push_back(std::move(button));}

bool PrintManager::print_objects_empty(){return printObjects.empty();}
bool PrintManager::print_texts_empty(){return printTexts.empty();}
bool PrintManager::print_buttons_empty(){return printButtons.empty();}

void PrintManager::clear_object_back(){printObjects.pop_back();}
void PrintManager::clear_text_back(){printTexts.pop_back();}
void PrintManager::clear_button_back(){printButtons.pop_back();}

bool PrintManager::object_back_alive()
{
    return !printObjects.empty()
        && printObjects.back()->isAlive()
        && !printObjects.back()->isImmortal();
}
bool PrintManager::text_back_alive()
{
    return !printTexts.empty()
        && printTexts.back()->alive()
        && !printTexts.back()->is_immortal();
}
bool PrintManager::button_back_alive()
{
    return !printButtons.empty()
        && printButtons.back()->alive()
        && !printButtons.back()->is_immortal();
}

