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
            none,
        };
    protected :
        LetManager pl;
        PrintManager pp;
        SoundManager ps;
        bool convert_page;

        const Name name;
    public :
        Page();
        virtual ~Page() = default;
        virtual PageSignal proceed_page(FileManager& pfs, sf::RenderWindow& window) = 0;
        LetManager& refer_let();
};