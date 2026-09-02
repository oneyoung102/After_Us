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

bool Entity::is_collided(const Entity& entity, const World& world) const
{
    if(*this == entity)
        return false;
    if(world[this->get_pos()].height != world[entity.get_pos()].height)
        return false;
    const auto hitbox1 = this->get_hitbox()/2.0;
    const auto hitbox2 = entity.get_hitbox()/2.0;
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

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/tree.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/bush.hpp"

void to_json(nlohmann::json& j, const std::shared_ptr<Entity>& entity)
{
    if (!entity) {
        j = nullptr;
        return;
    }
    j["name"] = entity->get_name();
    switch (entity->get_name())
    {
        case Entity::EntityName::player:
            j["data"] = *std::dynamic_pointer_cast<Player>(entity);
            break;
        case Entity::EntityName::tree:
            j["data"] = *std::dynamic_pointer_cast<Tree>(entity);
            break;
        case Entity::EntityName::fallen_item:
            j["data"] = *std::dynamic_pointer_cast<FallenItem>(entity);
            break;
        case Entity::EntityName::camera:
            j["data"] = *std::dynamic_pointer_cast<Camera>(entity);
            break;
        case Entity::EntityName::bush:
            j["data"] = *std::dynamic_pointer_cast<Bush>(entity);
            break;
        default:
            break;
    }
}

void from_json(const nlohmann::json& j, std::shared_ptr<Entity>& entity)
{
    if (j.is_null()) {
        entity = nullptr;
        return;
    }
    Entity::EntityName name = j.at("name").get<Entity::EntityName>();
    switch (name)
    {
        case Entity::EntityName::player: {
            auto p = std::make_shared<Player>();
            j.at("data").get_to(*p);
            entity = p;
            break;
        }
        case Entity::EntityName::tree: {
            auto t = std::make_shared<Tree>();
            j.at("data").get_to(*t);
            entity = t;
            break;
        }
        case Entity::EntityName::fallen_item: {
            auto f = std::make_shared<FallenItem>();
            j.at("data").get_to(*f);
            entity = f;
            break;
        }
        case Entity::EntityName::camera: {
            auto c = std::make_shared<Camera>();
            j.at("data").get_to(*c);
            entity = c;
            break;
        }
        case Entity::EntityName::bush: {
            auto b = std::make_shared<Bush>();
            j.at("data").get_to(*b);
            entity = b;
            break;
        }
        default:
            entity = nullptr;
            break;
    }
}