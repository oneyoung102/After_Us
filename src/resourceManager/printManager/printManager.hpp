#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "resourceManager/printManager/printObject/printObject.hpp"
#include "resourceManager/printManager/printText/printText.hpp"
#include "resourceManager/printManager/printButton/printButton.hpp"
#include "resourceManager/printManager/shader/shader.hpp"


class PrintManager
{
    private :
        std::vector<std::unique_ptr<PrintObjectInterface>> __print_objects;
        std::vector<std::unique_ptr<PrintText>> __print_texts;
        std::vector<std::unique_ptr<PrintButton>> __print_buttons;
        Shader shader;
    public :
        PrintManager();
        void print_objects(sf::RenderWindow& window);
        void print_texts(sf::RenderWindow& window);
        void print_buttons(sf::RenderWindow& window);

        void add_object(std::unique_ptr<PrintObjectInterface>&& object);
        void add_text(std::unique_ptr<PrintText>&& text);
        void add_button(std::unique_ptr<PrintButton>&& button);

        bool object_is_empty();
        bool text_is_empty();
        bool button_is_empty();

        void clear_object_back();
        void clear_text_back();
        void clear_button_back();

        bool object_back_is_alive();
        bool text_back_is_alive();
        bool button_back_is_alive();
};