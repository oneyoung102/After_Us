#include "entityManager.hpp"
#include "game/keyManager/keyboardManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "main/windowManager/windowManager.hpp"
#include "tools/cast.hpp"
#include "tools/pos.hpp"
#include <memory>

EntityManager::EntityManager(const World& world, std::vector<std::unique_ptr<Entity>>&& entities)
    : chunks(
        std::ceil(world.get_size().r / tools::CASTf(Chunk::CHUNK_SIZE)),
        std::vector<Chunk>(std::ceil(world.get_size().c/tools::CASTf(Chunk::CHUNK_SIZE)))
    )
{
    available_entity_code = Entity::UNREGISTERED;

    for(auto& entity : entities)
        register_entity(std::move(entity));
}

Chunk& EntityManager::get_chunk(const tools::POSs& pos)
{
    return chunks[pos.r][pos.c];
}
const Chunk& EntityManager::get_chunk(const tools::POSs& pos) const
{
    return chunks[pos.r][pos.c];
}
tools::POSs EntityManager::get_chunks_size() const
{
    return tools::POSs(chunks[0].size(),chunks.size());
}

bool EntityManager::is_valid_chunk(const tools::POSi& chunk_pos) const
{
    return chunk_pos.r >= 0 && chunk_pos.r < chunks.size() && chunk_pos.c >= 0 && chunk_pos.c < chunks[0].size();
}

void EntityManager::register_entity(std::shared_ptr<Entity> entity)
{
    if(entity->is_registered())
        throw std::runtime_error("entity is already registered");
    entity->set_entity_code(++available_entity_code);

    if(auto p = std::dynamic_pointer_cast<Player>(entity))
        player = p;
    const auto chunk_pos = get_chunk_pos(entity);
    get_chunk(chunk_pos).insert(std::move(entity));
}
 
void EntityManager::unregister_entity(const std::shared_ptr<const Entity>& entity)
{
    if(!entity->is_registered())
        throw std::runtime_error("entity is not registered");
    const auto chunk_pos = get_chunk_pos(entity);
    get_chunk(chunk_pos).erase(entity);
    if(auto p = std::dynamic_pointer_cast<const Player>(entity))
        if(player.lock() == p)
            player.reset();
}

void EntityManager::move_entity(const tools::POSf& prev_pos, const std::shared_ptr<Entity>& entity)
{
    const auto pos = entity->get_pos();
    const auto chunk_pos = get_chunk_pos(entity);
    const auto prev_chunk_pos = get_chunk_pos(prev_pos);
    if(prev_pos == pos || prev_chunk_pos == chunk_pos && prev_pos.y == pos.y)
        return;
    get_chunk(prev_chunk_pos).erase(entity);
    get_chunk(chunk_pos).insert(entity);
}

std::pair<tools::POSs,tools::POSs> EntityManager::get_update_chunk_range(const World& world, const Camera& camera) const
{
    const auto [start_world, end_world] = WindowManager::get_displayed_world_range(world, camera);
    const auto start_chunk = get_chunk_pos(start_world);
    const auto end_chunk = get_chunk_pos(end_world);

    auto start = tools::POSs(
        std::max(0, tools::CASTi(start_chunk.c) - UPDATE_CHUNK_DIAMETER),
        std::max(0, tools::CASTi(start_chunk.r) - UPDATE_CHUNK_DIAMETER));
    auto end = tools::POSs(
        std::min(tools::CASTi(chunks[0].size()), tools::CASTi(end_chunk.c) + UPDATE_CHUNK_DIAMETER + 1),
        std::min(tools::CASTi(chunks.size()), tools::CASTi(end_chunk.r) + UPDATE_CHUNK_DIAMETER + 1));
    
    return {start,end};
}

void EntityManager::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    const auto [start, end] = get_update_chunk_range(world_manager.get_world(), world_manager.get_camera());
    for (size_t r = start.r; r < end.r; ++r)
    {
        for (size_t c = start.c; c < end.c; ++c)
        {
            auto& chunk = chunks[r][c];
            for(size_t i = 0 ; i < chunk.get_dynamic_entities_size() ; i++)
            {
                auto entity_ptr = chunk.get_dynamic_entity_ptr(i);
                entity_ptr->update(window_manager, world_manager);

                if(auto creature = std::dynamic_pointer_cast<Creature>(entity_ptr))
                {
                    if(!creature->is_alive())
                        unregister_entity(entity_ptr);
                }
                if(auto moving_entity = std::dynamic_pointer_cast<MovingEntity>(entity_ptr))
                {
                    move_entity(moving_entity->get_prev_pos(), moving_entity);
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Entity>> EntityManager::find_collided_dynamic_entities(const Entity& entity)
{
    std::vector<std::shared_ptr<Entity>> collided_entities;
    const tools::POSi chunk_pos = get_chunk_pos(entity.get_pos());

    tools::POSi chunks_size = get_chunks_size();
    const tools::POSs start = {
        tools::CASTs(std::max(0, chunk_pos.c - 1)),
        tools::CASTs(std::max(0, chunk_pos.r - 1))};
    const tools::POSs end = {
        tools::CASTs(std::min(chunk_pos.c + 1, chunks_size.c - 1)),
        tools::CASTs(std::min(chunk_pos.r + 1, chunks_size.r - 1))};

    for (size_t row = start.r; row <= end.r; ++row)
        for (size_t col = start.c; col <= end.c; ++col)
        {
            tools::POSs chunk_pos(col, row);
            auto& chunk = get_chunk(chunk_pos);
            
            auto condition = [&entity](const Entity& object){
                if (object == entity)
                    return false;
                return entity.is_collided(object);
            };
            
            auto dynamic_entities = chunk.find_dynamic_entities(condition);
            collided_entities.insert(collided_entities.end(), dynamic_entities.begin(), dynamic_entities.end());
        } 
    
    return collided_entities;
}
bool EntityManager::is_collided(const Entity& entity)
{
    const tools::POSi chunk_pos = get_chunk_pos(entity.get_pos());

    tools::POSi chunks_size = get_chunks_size();
    const tools::POSs start = {
        tools::CASTs(std::max(0, chunk_pos.c - 1)),
        tools::CASTs(std::max(0, chunk_pos.r - 1))};
    const tools::POSs end = {
        tools::CASTs(std::min(chunk_pos.c + 1, chunks_size.c - 1)),
        tools::CASTs(std::min(chunk_pos.r + 1, chunks_size.r - 1))};

    for (size_t row = start.r; row <= end.r; ++row)
        for (size_t col = start.c; col <= end.c; ++col)
        {
            tools::POSs chunk_pos(col, row);
            auto& chunk = get_chunk(chunk_pos);
            
            for(size_t i = 0; i < chunk.get_static_entities_size(); ++i)
                if(entity.is_collided(chunk.get_static_entity(i)))
                    return true;
            for(size_t i = 0; i < chunk.get_dynamic_entities_size(); ++i)
                if(entity.is_collided(chunk.get_dynamic_entity(i)))
                    return true;
        } 
    
    return false;
}


void EntityManager::allot_player_keys(KeyboardManager& keyboard_Manager)
{
    keyboard_Manager.allot_key(sf::Keyboard::Key::W, [this](){player.lock()->move_up();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::S, [this](){player.lock()->move_down();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::A, [this](){player.lock()->move_left();});
    keyboard_Manager.allot_key(sf::Keyboard::Key::D, [this](){player.lock()->move_right();});
}

Player& EntityManager::get_player() {return *player.lock();}
const Player& EntityManager::get_player() const {return *player.lock();}
std::shared_ptr<Player> EntityManager::get_player_ptr(){return player.lock();}
std::shared_ptr<const Player> EntityManager::get_player_ptr() const{return player.lock();}

