#include "worldManager.hpp"
#include "tools/json.hpp"


WorldManager::WorldManager(tools::Tick time, Camera&& camera)
    : entity_manager(world)
    , time(time), tick(0)
    , camera(std::move(camera))
{
    world = tools::load_from_json<World>("world.json");
    try
    {
        entity_manager = tools::load_from_json<EntityManager>("entity_manager.json");
        entity_manager.rebind_player();
        if(entity_manager.get_chunks_size().r == 0 || entity_manager.get_chunks_size().c == 0)
            entity_manager = EntityManager(world, {});
    }
    catch (...)
    {
        entity_manager = EntityManager(world, {});
    }

    // JSON에 플레이어가 없으면 새로 생성 (has_player() 체크로 중복 방지) 임시임시임시임시임시임시임시임시
    entity_manager.generate_initial_entities(world);
}

WorldManager::~WorldManager()
{
    tools::save_to_json(world, "world.json");
    tools::save_to_json(entity_manager, "entity_manager.json");
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