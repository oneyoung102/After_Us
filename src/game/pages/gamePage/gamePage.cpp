#include "game/pages/gamePage/gamePage.hpp"
#include "game/pageManager/pageSignal.hpp"
#include "game/pages/gamePage/gameManager/thing/things/camera.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include "resourceManager/printManager/printObject/printWorld.hpp"

GamePage::GamePage(const FileManager& file_manager, WindowManager::ScreenSizeType screen_size)
    : world_manager(WorldManager(Camera()))
{
    print_manager.add_object(std::make_unique<PrintObject<WorldManager>>(world_manager,screen_size,file_manager.get_sprite(FileManager::Image::world_asset)));
}

PageSignal GamePage::proceed_page(FileManager& file_manager, sf::RenderWindow& window)
{
    PageSignal page_signal;
    
    print_manager.print_objects(window);
    world_manager.testCameraMove();

    return page_signal;
}
constexpr GamePage::Name GamePage::get_name() const {return Name::game;}
