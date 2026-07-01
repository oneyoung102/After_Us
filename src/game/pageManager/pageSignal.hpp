#pragma once

#include "game/pages/page.hpp"
#include <optional>


class PageSignal
{
    public :
        std::optional<Page::Name> nextPage;
        std::optional<bool> requestCapture;
};