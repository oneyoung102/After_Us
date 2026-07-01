#pragma once

#include <SFML/Graphics.hpp>
#include "game/pageManager/pageSignal.hpp"
#include "game/pages/page.hpp"
#include "resourceManager/fileManager/fileManager.hpp"

#include <memory>


class PageManager
{
    private : 
        FileManager pfs;
        std::unique_ptr<Page> curr_page;
        PageSignal signal;

        sf::Texture capture_texture;
        sf::Sprite capture_sprite;
        void captureWindow(sf::RenderWindow& window);

        void changePage(Page::Name p);
    public :
        PageManager();
        void showPage(sf::RenderWindow& window);

};