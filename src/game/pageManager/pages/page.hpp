#pragma once

#include "resourceManager/printManager/printManager.hpp"
#include "resourceManager/soundManager/soundManager.hpp"
#include "game/letManager/letManager.hpp"


class FileManager;
class RenderWindow;
class PageSignal;

class Page
{
    public :
        enum Name
        {
            game,
        };
    protected :
        LetManager let_manager;
        PrintManager print_manager;
        SoundManager sound_manager;
        bool convert_page;

    public :
        Page();
        virtual ~Page() = default;
        virtual PageSignal proceed_page(FileManager& file_manager, sf::RenderWindow& window) = 0;
        constexpr virtual Name get_name() const = 0;
        LetManager& get_let_manager();
};