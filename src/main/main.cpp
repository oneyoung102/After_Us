#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>
#include "game/pageManager/pageManager.hpp"
#include "main/windowManager/windowManager.hpp"
    
int main()
{   
    WindowManager windowManager("After Us");
    PageManager pageManager(windowManager.getScreenSize());
    while(windowManager.isOpen())
    {
        try
        {
            pageManager.showPage(windowManager);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            windowManager.close();
            break;
        }
    }
    return 0;
}
