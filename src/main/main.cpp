#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "main/windowResize/windowResize.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include "resourceManager/printManager/printManager.hpp"
#include "resourceManager/printManager/printObject/printWorld.hpp"
#include "tools/pos.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
    
int main()
{   
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const auto screenSize = tools::POSf(desktop.size.x, desktop.size.y);
    const auto screenCenter = screenSize / 2.0;
    const auto worldSize = tools::POSf(ceil(screenSize.x/imageConstant::BLOCK_SIZE.x),ceil(screenSize.y/imageConstant::BLOCK_SIZE.y));
    using WORLD_TYPE = std::vector<std::vector<imageConstant::BlockCode>>;
    WORLD_TYPE world(worldSize.y,std::vector<imageConstant::BlockCode>(worldSize.x,imageConstant::BlockCode::GRASS_1));

    const float RATIO = screenSize.x / screenSize.y;

    FileManager fileManager;
    PrintManager printManager;
    printManager.add_print_object(std::make_unique<PrintWorld>(world,screenSize,fileManager.getSprite(FileManager::Image::worldAsset)));

    sf::RenderWindow window(desktop, "After Us"); // 창 설정   
    sf::View view(sf::FloatRect({0.f, 0.f}, {screenSize.x, screenSize.y}));
    window.setView(view);
    
    window.setFramerateLimit(120); 
    while(window.isOpen())
    {
        try
        {
            while(auto event = window.pollEvent())
            {
                if(event->is<sf::Event::Closed>())
                    window.close();
                
                if(const auto* resized = getResizeEvent(*event))
                    view.setViewport(windowResize(resized, RATIO));
            }
            window.clear(sf::Color::Black);
            printManager.print_all_objects(window);
            
            window.setView(view);
            window.display();
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            window.close();
            break;
        }
    }
    return 0;
}
