#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>
#include "game/pageManager/pageManager.hpp"
#include "main/windowManager/windowManager.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
    
int main()
{   
    WindowManager window_manager("After Us");
    PageManager page_manager(window_manager.get_screen_size());
    while(window_manager.is_open())
    {
        try
        {
            page_manager.show_page(window_manager);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            window_manager.close();
            break;
        }
    }
    return 0;
}
