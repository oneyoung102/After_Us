#include "entity.hpp"
Entity::Entity(const tools::POSf& pos, float size)
    : pos(pos)
    , size(size)
    , entity_code(UNREGISTERED)
{
}

tools::POSf Entity::get_pos() const {return pos;}
float Entity::get_size() const {return size;}

void Entity::set_pos(const tools::POSf& pos){this->pos = pos;}
void Entity::set_pos(tools::POSf&& pos){this->pos = std::move(pos);}
void Entity::set_size(float size){this->size = size;}

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
    const auto hitbox1 = this->get_hitbox();
    const auto hitbox2 = entity.get_hitbox();
    const tools::POSf rect_min1 = this->pos-hitbox1;
    const tools::POSf rect_max1 = this->pos+hitbox1;
    const tools::POSf rect_min2 = entity.pos-hitbox2;
    const tools::POSf rect_max2 = entity.pos+hitbox2;
    if(rect_max1.x < rect_min2.x || rect_max2.x < rect_min1.x)
        return false;
    if(rect_max1.y < rect_min2.y || rect_max2.y < rect_min1.y)
        return false;
    return true;
}