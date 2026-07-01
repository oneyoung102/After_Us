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

void PrintManager::printObjects(RenderWindow& window)
{
    for(int i = 0 ; i < __printObjects.size() ; )
        if(__printObjects[i]->isAlive())
        {
            __printObjects[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(__printObjects[i], __printObjects.back());
            __printObjects.pop_back();
        }
}
void PrintManager::printTexts(RenderWindow& window)
{
    for(int i = 0 ; i < __printTexts.size() ; )
        if(__printTexts[i]->isAlive())
        {
            __printTexts[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(__printTexts[i], __printTexts.back());
            __printTexts.pop_back();
        }
}
void PrintManager::printButtons(RenderWindow& window)
{
    for(int i = 0 ; i < __printButtons.size() ; )
        if(__printButtons[i]->isAlive())
        {
            __printButtons[i]->print(window, shader);
            ++i;
        }
        else
        {
            std::swap(__printButtons[i], __printButtons.back());
            __printButtons.pop_back();
        }
}

void PrintManager::addObject(unique_ptr<PrintObject>&& object){__printObjects.push_back(std::move(object));}
void PrintManager::addText(unique_ptr<PrintText>&& text){__printTexts.push_back(std::move(text));}
void PrintManager::addButton(unique_ptr<PrintButton>&& button){__printButtons.push_back(std::move(button));}

bool PrintManager::objectIsEmpty(){return __printObjects.empty();}
bool PrintManager::textIsEmpty(){return __printTexts.empty();}
bool PrintManager::buttonIsEmpty(){return __printButtons.empty();}

void PrintManager::clearObjectBack(){__printObjects.pop_back();}
void PrintManager::clearTextBack(){__printTexts.pop_back();}
void PrintManager::clearButtonBack(){__printButtons.pop_back();}

bool PrintManager::objectBackIsAlive()
{
    return !__printObjects.empty()
        && __printObjects.back()->isAlive()
        && !__printObjects.back()->isImmortal();
}
bool PrintManager::textBackIsAlive()
{
    return !__printTexts.empty()
        && __printTexts.back()->isAlive()
        && !__printTexts.back()->isImmortal();
}
bool PrintManager::buttonBackIsAlive()
{
    return !__printButtons.empty()
        && __printButtons.back()->isAlive()
        && !__printButtons.back()->isImmortal();
}

