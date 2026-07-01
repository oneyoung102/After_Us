#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "printObject/printObject.hpp"
#include "printText/printText.hpp"
#include "printButton/printButton.hpp"


class PrintManager
{
    private :
        std::vector<std::unique_ptr<PrintObject>> printObjects;
        std::vector<std::unique_ptr<PrintText>> printTexts;
        std::vector<std::unique_ptr<PrintButton>> printButtons;
        sf::Shader shader;
    public :
        PrintManager();
        void print_all_objects(sf::RenderWindow& window);
        void print_all_texts(sf::RenderWindow& window);
        void print_all_buttons(sf::RenderWindow& window);

        void add_print_object(std::unique_ptr<PrintObject>&& object);
        void add_print_text(std::unique_ptr<PrintText>&& text);
        void add_print_button(std::unique_ptr<PrintButton>&& button);

        bool print_objects_empty();
        bool print_texts_empty();
        bool print_buttons_empty();

        void clear_object_back();
        void clear_text_back();
        void clear_button_back();

        bool object_back_alive();
        bool text_back_alive();
        bool button_back_alive();
};