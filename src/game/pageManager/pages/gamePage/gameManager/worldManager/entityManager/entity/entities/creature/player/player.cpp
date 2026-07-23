#include "player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

Player::Player(const tools::POSf& pos)
    : Creature(pos, 0.8f, DEFAULT_SPEED, 1, 100, 100, 10, 10, 0.4f, 10.0f)
{
    set_reach(0.75);
    __main_hand_action = [this](const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer){
        interact(pointer_pos, find_collided_entites_by_pointer);
    };
}

void Player::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    Creature::update(window_manager, world_manager);
}

void Player::set_reach(float reach)
{
    if(reach < 0)
        throw std::runtime_error("reach of player must be positive");
    this->reach = reach;
}
float Player::get_reach() const {return reach;}

tools::POSf Player::get_hitbox() const {return tools::POSf(0.4f,0.2f)*size;} //hitbox를 size로, 바닥크기 추가, setter,getter 추가

void Player::interact(const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer)
{
    auto collided_entites = find_collided_entites_by_pointer();
    if(collided_entites.empty())
        return;
    std::shared_ptr<InteractableEntity> entity;
    for(auto& collided_entity : collided_entites)
        if(auto interactable_entity = std::dynamic_pointer_cast<InteractableEntity>(collided_entity))
        {
            if(!entity || entity->get_pos().square_size() > interactable_entity->get_pos().square_size())
                entity = interactable_entity;
        }
    if(!entity)
        return;
    entity->set_interacted_state(true);
}

void Player::main_hand_action(const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer) {
    if(!__main_hand_action)
        return;
    __main_hand_action(pointer_pos,find_collided_entites_by_pointer);
}
void Player::off_hand_action(const tools::POSf& pointer_pos, const std::function<std::vector<std::shared_ptr<Entity>>()>& find_collided_entites_by_pointer) {
    if(!__off_hand_action)
        return;
    __off_hand_action(pointer_pos,find_collided_entites_by_pointer);
}
