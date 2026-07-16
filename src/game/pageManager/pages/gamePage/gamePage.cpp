#include "game/pageManager/pages/gamePage/gamePage.hpp"
#include "game/pageManager/pageSignal.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "resourceManager/fileManager/fileManager.hpp"

#include "resourceManager/printManager/printObject/printWorld.hpp"
#include "resourceManager/printManager/printObject/printEntities.hpp"
#include "resourceManager/printManager/printObject/printPointer.hpp"

GamePage::GamePage(const FileManager& file_manager)
    : world_manager(WorldManager(0,Camera()))
{
    print_manager.add_object(std::make_unique<PrintObject<World>>(file_manager.get_image_datas(),world_manager));
    print_manager.add_object(std::make_unique<PrintObject<Entity>>(file_manager.get_image_datas(),world_manager));
    print_manager.add_object(std::make_unique<PrintObject<Pointer>>(file_manager.get_image_datas(),world_manager, mouse_manager));

    auto& camera = world_manager.get_camera();
    auto& entity_manager = world_manager.get_entity_manager();

    entity_manager.register_entity(std::make_unique<Player>(tools::POSf(1,1)));

    entity_manager.allot_player_keys(keyboard_manager);//키보드 메니져에 메핑 만들고 그 클래스에 위임
    mouse_manager.allot_key(sf::Mouse::Button::Left, [this, &entity_manager](){
        entity_manager.get_player().main_hand_action(
            mouse_manager.get_pointer().get_pos(),
            [this,&entity_manager](){
                return entity_manager.find_collided_dynamic_entities(mouse_manager.get_pointer());
            }
        );
    });
    mouse_manager.allot_key(sf::Mouse::Button::Right, [this, &entity_manager](){
        entity_manager.get_player().off_hand_action(
            mouse_manager.get_pointer().get_pos(),
            [this,&entity_manager](){
                return entity_manager.find_collided_dynamic_entities(mouse_manager.get_pointer());
            }
        );
    });
    camera.target(entity_manager.get_player_ptr());
}

PageSignal GamePage::proceed_page(FileManager& file_manager, WindowManager& window_manager)
{
    PageSignal page_signal;
    
    print_manager.print_objects(window_manager.get_window());
    world_manager.update(window_manager);
    mouse_manager.show_mouse_cursor(window_manager.get_window(),false); // 인벤토리 열거나 이럴 때 true 할 예정

    mouse_manager.anchor_mouse(window_manager, world_manager.get_camera(), world_manager.get_entity_manager().get_player());


    return page_signal;
}
constexpr GamePage::Name GamePage::get_name() const {return Name::game;}
