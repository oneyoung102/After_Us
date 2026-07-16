#include "chunk.hpp"

Entity& Chunk::get_static_entity(size_t idx) {return *static_entities[idx];}
Entity& Chunk::get_dynamic_entity(size_t idx) {return *dynamic_entities[idx];}
const Entity& Chunk::get_static_entity(size_t idx) const {return *static_entities[idx];}
const Entity& Chunk::get_dynamic_entity(size_t idx) const {return *dynamic_entities[idx];}

std::shared_ptr<Entity> Chunk::get_static_entity_ptr(size_t idx) {return static_entities[idx];}
std::shared_ptr<Entity> Chunk::get_dynamic_entity_ptr(size_t idx) {return dynamic_entities[idx];}
std::shared_ptr<const Entity> Chunk::get_static_entity_ptr(size_t idx) const {return static_entities[idx];}
std::shared_ptr<const Entity> Chunk::get_dynamic_entity_ptr(size_t idx) const {return dynamic_entities[idx];}

size_t Chunk::get_static_entities_size() const {return static_entities.size();}
size_t Chunk::get_dynamic_entities_size() const {return dynamic_entities.size();}

void Chunk::insert(std::shared_ptr<Entity> entity)
{
    auto* entities = &static_entities;
    if(entity->is_dynamic_entity())
        entities = &dynamic_entities;

    auto pos = entity->get_pos();
    auto it = std::lower_bound(entities->begin(), entities->end(), pos.y, [](const std::shared_ptr<Entity>& a, float val){
        return a->get_pos().y < val;
    });
    entities->insert(it, std::move(entity));
}

void Chunk::erase(const std::shared_ptr<const Entity>& entity) 
{
    auto* entities = &static_entities;
    if(entity->is_dynamic_entity())
        entities = &dynamic_entities;
    
    auto it = std::find(entities->begin(), entities->end(), entity);
    if (it != entities->end())
        entities->erase(it);
}

std::shared_ptr<Entity> Chunk::find_static_entity(const std::function<bool(const Entity&, const Entity&)>& condition)
{
    if (static_entities.empty()) return nullptr;
    auto entity = static_entities[0];
    for (size_t i = 1; i < static_entities.size(); ++i)
        if (condition(*static_entities[i], *entity))
            entity = static_entities[i];
    return entity;
}

std::shared_ptr<Entity> Chunk::find_dynamic_entity(const std::function<bool(const Entity&, const Entity&)>& condition)
{
    if (dynamic_entities.empty()) return nullptr;
    auto entity = dynamic_entities[0];
    for (size_t i = 1; i < dynamic_entities.size(); ++i)
        if (condition(*dynamic_entities[i], *entity))
            entity = dynamic_entities[i];
    return entity;
}

std::vector<std::shared_ptr<Entity>> Chunk::find_static_entities(const std::function<bool(const Entity&)>& condition)
{
    std::vector<std::shared_ptr<Entity>> entities;
    for (size_t i = 0; i < static_entities.size(); ++i)
        if (condition(*static_entities[i]))
            entities.push_back(static_entities[i]);
    return entities;
}

std::vector<std::shared_ptr<Entity>> Chunk::find_dynamic_entities(const std::function<bool(const Entity&)>& condition)
{
    std::vector<std::shared_ptr<Entity>> entities;
    for (size_t i = 0; i < dynamic_entities.size(); ++i)
        if (condition(*dynamic_entities[i]))
            entities.push_back(dynamic_entities[i]);
    return entities;
}