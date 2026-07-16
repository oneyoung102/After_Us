#pragma once

#include "game/keyManager/mouseManager.hpp"
#include "main/windowManager/windowManager.hpp"
#include "resourceManager/printManager/printManager.hpp"
#include "resourceManager/soundManager/soundManager.hpp"
#include "game/keyManager/keyboardManager.hpp"


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
        KeyboardManager keyboard_manager;
        MouseManager mouse_manager;
        PrintManager print_manager;
        SoundManager sound_manager;
        bool convert_page;

    public :
        Page();
        virtual ~Page() = default;
        virtual PageSignal proceed_page(FileManager& file_manager, WindowManager& window_manager) = 0;
        constexpr virtual Name get_name() const = 0;
        KeyboardManager& get_keyboard_manager();
        MouseManager& get_mouse_manager();
};