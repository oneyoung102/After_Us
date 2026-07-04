#pragma once

#include <SFML/Graphics.hpp>
#include "game/pageManager/pageSignal.hpp"
#include "game/pageManager/pages/page.hpp"
#include "main/windowManager/windowManager.hpp"
#include "resourceManager/fileManager/fileManager.hpp"

#include <memory>


class PageManager
{
    private : 
        FileManager file_manager;
        std::unique_ptr<Page> curr_page;
        PageSignal signal;

        const WindowManager::ScreenSizeType screen_size;

        void change_page(Page::Name page_name);
    public :
        PageManager(WindowManager::ScreenSizeType screen_size);
        void show_page(WindowManager& window_manager);

};