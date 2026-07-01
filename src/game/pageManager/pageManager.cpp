#include "game/pageManager/pageManager.hpp"
#include "game/pages/page.hpp"
#include "game/pageManager/pageSignal.hpp"

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

void PageManager::changePage(Page::Name p)
{

}

void PageManager::captureWindow(sf::RenderWindow& window)
{
    capture_texture = sf::Texture(window.getSize()); 
    capture_texture.update(window);
    capture_sprite.setTexture(capture_texture, true);
}

PageManager::PageManager()
    : capture_sprite(Sprite(capture_texture))
    , signal{}
{
    changePage(*signal.next_page);
}

void PageManager::showPage(sf::RenderWindow& window)
{
    while (auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        curr_page->refer_let().act_keyboard_let(event);
    }
    window.clear();
    signal = curr_page->proceed_page(pfs, window);
    window.display();
    
    if(signal.request_capture && *signal.request_capture)
    {
        captureWindow(window);
        signal.request_capture = false;

    }
    if(signal.next_page)
        changePage(*signal.next_page);
}
