#include "game/pageManager/pages/page.hpp"

Page::Page()
    : convert_page(false)
{}
LetManager& Page::get_let_manager(){return let_manager;}