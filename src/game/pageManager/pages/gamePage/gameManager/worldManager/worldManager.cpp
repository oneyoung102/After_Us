#include "worldManager.hpp"

WorldManager::WorldManager(Camera&& camera)
    : thing_manager(world)
    , camera(std::move(camera))
{
    //world = ; 여기서 파일에서 월드 불러오기
    thing_manager = ThingManager(world);
}

const World& WorldManager::get_world() const {return world;}
World& WorldManager::get_world(){return world;}

const Camera& WorldManager::get_camera() const {return camera;}
Camera& WorldManager::get_camera(){return camera;}

const ThingManager& WorldManager::get_thing_manager() const {return thing_manager;}
ThingManager& WorldManager::get_thing_manager(){return thing_manager;}
