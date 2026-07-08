#include "entity.hpp"

Entity::Entity(const tools::POSf& pos, float size)
    : pos(pos)
    , entity_code(UNREGISTERED)
{
    set_size(size);
}

tools::POSf Entity::get_pos() const {return pos;}
float Entity::get_size() const {return size;}

void Entity::set_pos(const tools::POSf& pos){this->pos = pos;}
void Entity::set_pos(const tools::POSf&& pos){this->pos = std::move(pos);}
void Entity::set_size(float size)
{
    if(size < 0)
        throw std::runtime_error("entity size is less than 0");
    this->size = size;
}

World::Tile Entity::get_curr_tile(const World& world) const
{
    return world[tools::POSs(pos)];
}
int Entity::get_curr_height(const World& world) const
{
    return world.get_height(tools::POSs(pos));
}

bool Entity::is_registered() const {return entity_code != UNREGISTERED;}
Entity::ENTITY_CODE Entity::get_entity_code() const {return entity_code;}
void Entity::set_entity_code(Entity::ENTITY_CODE entity_code)
{
    if(is_registered())
        throw std::runtime_error("entity is already registered");
    this->entity_code = entity_code;
}