#include "game/pageManager/pages/page.hpp"

Page::Page()
    : convert_page(false)
{}
KeyboardManager& Page::get_keyboard_manager(){return keyboard_manager;}
MouseManager& Page::get_mouse_manager() {return mouse_manager;}