#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "printObject/printObject.hpp"
#include "printText/printText.hpp"
#include "printButton/printButton.hpp"


class PrintManager
{
    private :
        std::vector<std::unique_ptr<PrintObject>> __printObjects;
        std::vector<std::unique_ptr<PrintText>> __printTexts;
        std::vector<std::unique_ptr<PrintButton>> __printButtons;
        sf::Shader shader;
    public :
        PrintManager();
        void printObjects(sf::RenderWindow& window);
        void printTexts(sf::RenderWindow& window);
        void printButtons(sf::RenderWindow& window);

        void addObject(std::unique_ptr<PrintObject>&& object);
        void addText(std::unique_ptr<PrintText>&& text);
        void addButton(std::unique_ptr<PrintButton>&& button);

        bool objectIsEmpty();
        bool textIsEmpty();
        bool buttonIsEmpty();

        void clearObjectBack();
        void clearTextBack();
        void clearButtonBack();

        bool objectBackIsAlive();
        bool textBackIsAlive();
        bool buttonBackIsAlive();
};