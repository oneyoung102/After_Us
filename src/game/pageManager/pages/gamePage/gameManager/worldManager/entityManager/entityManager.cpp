#include "entityManager.hpp"
#include "game/letManager/letManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "main/windowManager/windowManager.hpp"
#include "tools/cast.hpp"
#include <cmath>
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
    return tools::POSs(chunks.size(), chunks[0].size());
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
    get_chunk(prev_chunk_pos).erase(entity,prev_pos.y);
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

void EntityManager::update(const WorldManager& world_manager)
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
                if(auto moving_entity = std::dynamic_pointer_cast<MovingEntity>(entity_ptr))
                {
                    move_entity(moving_entity->get_prev_pos(), moving_entity);
                    moving_entity->sync_prev_pos();
                }
            }
        }
    }
}

void EntityManager::allot_player_keys(LetManager& let_manager)
{
    let_manager.allot_state_key(sf::Keyboard::Key::W, [this](){player.lock()->move_up();});
    let_manager.allot_state_key(sf::Keyboard::Key::S, [this](){player.lock()->move_down();});
    let_manager.allot_state_key(sf::Keyboard::Key::A, [this](){player.lock()->move_left();});
    let_manager.allot_state_key(sf::Keyboard::Key::D, [this](){player.lock()->move_right();});
}

Player& EntityManager::get_player()
{
    return *player.lock();
}
const Player& EntityManager::get_player() const
{
    return *player.lock();
}
std::shared_ptr<Player> EntityManager::get_player_ptr()
{
    return player.lock();
}
std::shared_ptr<const Player> EntityManager::get_player_ptr() const
{
    return player.lock();
}

