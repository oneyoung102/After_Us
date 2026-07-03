#include "worldManager.hpp"

WorldManager::WorldManager(Camera&& camera)
    : camera(std::move(camera))
{
    //world = ; 여기서 파일에서 월드 불러오기
}

const World& WorldManager::get_world() const {return world;}
World& WorldManager::get_world(){return world;}

const Camera& WorldManager::get_camera() const {return camera;}
Camera& WorldManager::get_camera(){return camera;}
