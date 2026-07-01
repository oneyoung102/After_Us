#include "game/pages/page.hpp"

Page::Page()
    : convert_page(false)
    , name(Name::none)
{}
LetManager& Page::refer_let(){return pl;}