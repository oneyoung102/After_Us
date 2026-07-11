#include "game/pageManager/pageManager.hpp"
#include "game/pageManager/pages/gamePage/gamePage.hpp"
#include "game/pageManager/pages/page.hpp"
#include "game/pageManager/pageSignal.hpp"

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

void PageManager::change_page(Page::Name page_name)
{
    switch(page_name)
    {
        case Page::Name::game :
            curr_page = make_unique<GamePage>(file_manager);
    }
}

PageManager::PageManager()
    : signal{}
{
    signal.next_page = Page::Name::game;
    change_page(*signal.next_page);
    if(!curr_page)
        throw std::runtime_error("first page is not designated");
}

void PageManager::show_page(WindowManager& window_manager)
{
    while(auto event = window_manager.poll_event())
    {
        if(event->is<Event::Closed>())
            window_manager.close();
        window_manager.resize_window(event);
        curr_page->get_let_manager().act_event_let(event);
    }
    curr_page->get_let_manager().act_state_let();
    
    window_manager.clear();
    signal = curr_page->proceed_page(file_manager, window_manager);
    window_manager.set_view();
    window_manager.display();
    
    if(signal.request_capture && *signal.request_capture)
    {
        window_manager.capture_window();
        signal.request_capture = false;
    }
    if(signal.next_page)
        change_page(*signal.next_page);
}
