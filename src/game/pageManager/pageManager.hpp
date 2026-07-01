#pragma once

#include <SFML/Graphics.hpp>
#include "game/pageManager/pageSignal.hpp"
#include "game/pages/page.hpp"
#include "main/windowManager/windowManager.hpp"
#include "resourceManager/fileManager/fileManager.hpp"

#include <memory>


class PageManager
{
    private : 
        FileManager fileManager;
        std::unique_ptr<Page> currPage;
        PageSignal signal;

        const WindowManager::SCREEN_SIZE_TYPE screenSize;

        void changePage(Page::Name pageName);
    public :
        PageManager(WindowManager::SCREEN_SIZE_TYPE screenSize);
        void showPage(WindowManager& windowManager);

};