#include "game/pageManager/pages/gamePage/gamePage.hpp"
#include "game/pageManager/pageSignal.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include "resourceManager/printManager/printObject/printWorld.hpp"

GamePage::GamePage(const FileManager& file_manager)
    : world_manager(WorldManager(0,Camera()))
{
    print_manager.add_object(std::make_unique<PrintObject<WorldManager>>(file_manager.get_image_datas()[ImageDatas::Name::world],world_manager));

    auto& camera = world_manager.get_camera();
    auto& entity_manager = world_manager.get_entity_manager();

    entity_manager.register_entity(std::make_unique<Player>(tools::POSf(1,1)));
    entity_manager.allot_player_keys(let_manager);

    camera.target(entity_manager.get_player());
}

PageSignal GamePage::proceed_page(FileManager& file_manager, sf::RenderWindow& window)
{
    PageSignal page_signal;
    
    print_manager.print_objects(window);
    world_manager.get_camera().trace();


    return page_signal;
}
constexpr GamePage::Name GamePage::get_name() const {return Name::game;}
