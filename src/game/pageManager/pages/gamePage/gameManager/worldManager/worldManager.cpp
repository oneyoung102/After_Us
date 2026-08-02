#include "worldManager.hpp"
#include "tools/json.hpp"


WorldManager::WorldManager(tools::Tick time, Camera&& camera)
    : entity_manager(world)
    , time(time), tick(0)
    , camera(std::move(camera))
{
    world = tools::load_from_json<World>("world.json");
    entity_manager = EntityManager(world,{}); // {} : entities에 플레이어도 포함
}

WorldManager::~WorldManager()
{
    tools::save_to_json(world,"world.json");
}

void WorldManager::spend_time()
{
    ++tick;
    if(tick == 16)
    {
        tick = 0;
        ++time;
        if(time == ONE_DAY)
            time = 0;
    }
}

const tools::Tick& WorldManager::get_time() const {return time;}

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
    spend_time();
}