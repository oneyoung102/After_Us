#include "entity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/chunk/chunk.hpp"

Entity::Entity(const tools::POSf& pos, tools::POSf size)
    : pos(pos)
    , entity_code(UNREGISTERED)
{
    set_size(size);
}

tools::POSf Entity::get_pos() const {return pos;}
tools::POSf Entity::get_size() const {return size;}

void Entity::set_pos(const tools::POSf& pos){this->pos = pos;}
void Entity::set_pos(tools::POSf&& pos){this->pos = std::move(pos);}
void Entity::set_size(const tools::POSf& size)
{
    if(size.x < 0 || size.y < 0)
        throw std::runtime_error("entity size is less than 0");
    if(size.x > Chunk::CHUNK_SIZE/2.0 || size.y > Chunk::CHUNK_SIZE/2.0)
        throw std::runtime_error("entity size is greater than chunk size");
    this->size = size;
}

bool Entity::is_registered() const {return entity_code != UNREGISTERED;}
Entity::ENTITY_CODE Entity::get_entity_code() const {return entity_code;}
void Entity::set_entity_code(Entity::ENTITY_CODE entity_code)
{
    if(is_registered())
        throw std::runtime_error("entity is already registered");
    this->entity_code = entity_code;
}

bool Entity::is_collided(const Entity& entity) const
{
    if(*this == entity)
        return false;
    const tools::POSf rect_min1 = this->pos-this->size;
    const tools::POSf rect_max1 = this->pos+this->size;
    const tools::POSf rect_min2 = entity.pos-entity.size;
    const tools::POSf rect_max2 = entity.pos+entity.size;
    if(rect_max1.x <= rect_min2.x || rect_max2.x <= rect_min1.x)
        return false;
    if(rect_max1.y <= rect_min2.y || rect_max2.y <= rect_min1.y)
        return false;
    return true;
}