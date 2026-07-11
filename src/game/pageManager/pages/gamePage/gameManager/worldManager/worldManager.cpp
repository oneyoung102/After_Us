#include "worldManager.hpp"

WorldManager::WorldManager(Tick time, Camera&& camera)
    : entity_manager(world)
    , time(time)
    , camera(std::move(camera))
{
    //world = ; 여기서 파일에서 월드 불러오기
    entity_manager = EntityManager(world,{}); // {} : entities에 플레이어도 포함
}

const World& WorldManager::get_world() const {return world;}
World& WorldManager::get_world(){return world;}

const Camera& WorldManager::get_camera() const {return camera;}
Camera& WorldManager::get_camera(){return camera;}


const EntityManager& WorldManager::get_entity_manager() const {return entity_manager;}
EntityManager& WorldManager::get_entity_manager(){return entity_manager;}

void WorldManager::update(const WindowManager& window_manager)
{
    entity_manager.update(window_manager,*this);
    camera.trace();
}