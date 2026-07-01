#include "game/pageManager/pageManager.hpp"
#include "game/pages/gamePage/gamePage.hpp"
#include "game/pages/page.hpp"
#include "game/pageManager/pageSignal.hpp"

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

void PageManager::changePage(Page::Name pageName)
{
    switch(pageName)
    {
        case Page::Name::game :
            currPage = make_unique<GamePage>(fileManager, screenSize);
    }
}

PageManager::PageManager(WindowManager::SCREEN_SIZE_TYPE screenSize)
    : signal{}
    , screenSize(screenSize)
{
    signal.nextPage = Page::Name::game;
    changePage(*signal.nextPage);
    if(!currPage)
        throw std::runtime_error("first page is not designated");
}

void PageManager::showPage(WindowManager& windowManager)
{
    while(auto event = windowManager.pollEvent())
    {
        if(event->is<Event::Closed>())
            windowManager.close();
        windowManager.resizeWindow(event);
        currPage->getLetManager().actKeyboardLet(event);
    }
    windowManager.clear();
    signal = currPage->proceedPage(fileManager, windowManager.getWindow());
    windowManager.setView();
    windowManager.display();
    
    if(signal.requestCapture && *signal.requestCapture)
    {
        windowManager.captureWindow();
        signal.requestCapture = false;
    }
    if(signal.nextPage)
        changePage(*signal.nextPage);
}
