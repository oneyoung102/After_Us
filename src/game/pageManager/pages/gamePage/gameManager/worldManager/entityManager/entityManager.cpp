#include "entityManager.hpp"
#include "game/letManager/letManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include <cmath>

EntityManager::EntityManager(const World& world)
    : chunks(
        std::ceil(world.get_size().r / tools::CASTf(CHUNK_SIZE)),
        std::vector<ONE_CHUNK_TYPE>(std::ceil(world.get_size().c/tools::CASTf(CHUNK_SIZE)),
        ONE_CHUNK_TYPE(CHUNK_SIZE))
    )
{
    available_entity_codes.fill(Entity::UNREGISTERED+1);
}

EntityManager::ONE_CHUNK_TYPE& EntityManager::get_chunk(const tools::POSs& pos)
{
    return chunks[pos.r][pos.c];
}
const EntityManager::ONE_CHUNK_TYPE& EntityManager::get_chunk(const tools::POSs& pos) const
{
    return chunks[pos.r][pos.c];
}
tools::POSs EntityManager::get_chunks_size() const
{
    return tools::POSs(chunks.size(), chunks[0].size());
}

void EntityManager::register_entity(std::shared_ptr<Entity>&& entity)
{
    if(entity->is_registered())
        throw std::runtime_error("entity is already registered");
    const int idx = tools::CASTs(entity->get_name());
    entity->set_entity_code(available_entity_codes[idx]++);

    const auto chunk_pos = get_chunk_pos(entity);
    const auto row_in_chunk = get_row_in_chunk(entity);
    chunks[chunk_pos.r][chunk_pos.c].at(row_in_chunk).push_back(entity.get());

    if(auto p = std::dynamic_pointer_cast<Player>(entity))
        player = std::move(p);
    else if(auto creature = std::dynamic_pointer_cast<Creature>(entity))
        creatures.push_back(std::move(creature));
    else if(auto fallen_item = std::dynamic_pointer_cast<FallenItem>(entity))
        fallen_items.push_back(std::move(fallen_item));
    else if(auto thing = std::dynamic_pointer_cast<Thing>(entity))
        things.push_back(std::move(thing));
    else
        throw std::runtime_error("unknown entity type");
}
 
void EntityManager::unregister_entity(std::shared_ptr<Entity> entity)
{
    if(!entity->is_registered())
        throw std::runtime_error("entity is not registered");
    const auto chunk_pos = get_chunk_pos(entity);
    const auto row_in_chunk = get_row_in_chunk(entity);

    auto& row = chunks[chunk_pos.r][chunk_pos.c][row_in_chunk];
    for(size_t i = 0 ; i < row.size() ;)
        if(!row[i] || row[i] == entity.get() && row[i]->get_entity_code() == entity->get_entity_code())
        {
            std::swap(row[i], row.back());
            row.pop_back();
            break;
        }
        else
            i++;

    if(auto p = std::dynamic_pointer_cast<Player>(entity))
    {
        if(player && player->get_entity_code() == p->get_entity_code())
            player.reset();
    }
    else if(auto creature = std::dynamic_pointer_cast<Creature>(entity))
    {
        for(size_t i = 0 ; i < creatures.size() ;)
            if(!creatures[i] || (creatures[i] == entity && creatures[i]->get_entity_code() == entity->get_entity_code()))
            {
                std::swap(creatures[i], creatures.back());
                creatures.pop_back();
                break;
            }
            else
                i++;
    }
    else if(auto fallen_item = std::dynamic_pointer_cast<FallenItem>(entity))
    {
        for(size_t i = 0 ; i < fallen_items.size() ;)
            if(!fallen_items[i] || (fallen_items[i] == entity && fallen_items[i]->get_entity_code() == entity->get_entity_code()))
            {
                std::swap(fallen_items[i], fallen_items.back());
                fallen_items.pop_back();
                break;
            }
            else
                i++;
    }
    else if(auto thing = std::dynamic_pointer_cast<Thing>(entity))
    {
        for(size_t i = 0 ; i < things.size() ;)
            if(!things[i] || (things[i] == entity && things[i]->get_entity_code() == entity->get_entity_code()))
            {
                    std::swap(things[i], things.back());
                    things.pop_back();
                    break;
            }
            else
                i++;
    }
}

void EntityManager::move_entity(const tools::POSf& prev_pos, std::shared_ptr<Entity> entity)
{
    const auto prev_chunk_pos = get_chunk_pos(prev_pos);
    const auto prev_row_in_chunk = get_row_in_chunk(prev_pos.r);

    auto& row = chunks[prev_chunk_pos.r][prev_chunk_pos.c][prev_row_in_chunk];
    for(size_t i = 0 ; i < row.size() ;)
        if(!row[i] || row[i] == entity.get() && row[i]->get_entity_code() == entity->get_entity_code())
        {
            std::swap(row[i], row.back());
            row.pop_back();
            break;
        }
        else
            i++;
    const auto chunk_pos = get_chunk_pos(entity);
    const auto row_in_chunk = get_row_in_chunk(entity);
    chunks[chunk_pos.r][chunk_pos.c].at(row_in_chunk).push_back(entity.get());
}

void EntityManager::update_players(const WorldManager& world_manager)
{
    
}
void update_creatures(const WorldManager& world_manager)
{
    
}
void EntityManager::allot_player_keys(LetManager& let_manager)
{
    let_manager.allot_state_key(sf::Keyboard::Key::W, [this](){player->move_up();});
    let_manager.allot_state_key(sf::Keyboard::Key::S, [this](){player->move_down();});
    let_manager.allot_state_key(sf::Keyboard::Key::A, [this](){player->move_left();});
    let_manager.allot_state_key(sf::Keyboard::Key::D, [this](){player->move_right();});
}
std::shared_ptr<Player> EntityManager::get_player(){return player;}

