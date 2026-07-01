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
        LetManager letManager;
        PrintManager printManager;
        SoundManager soundManager;
        bool convertPage;

    public :
        Page();
        virtual ~Page() = default;
        virtual PageSignal proceedPage(FileManager& fileManager, sf::RenderWindow& window) = 0;
        constexpr virtual Name getName() const = 0;
        LetManager& getLetManager();
};