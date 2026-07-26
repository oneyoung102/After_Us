#include "player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

Player::Player(const tools::POSf& pos)
    : Creature(pos, 0.9f, DEFAULT_SPEED, 1, 100, 100, 10, 10, 0.4f, 10.0f)
{
    set_reach(0.75);
    __main_hand_action = [this](__HAND_ACTION_ARGUMENTS){
        interact(pointer_pos, world, find_collided_entites_by_pointer);
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

tools::POSf Player::get_hitbox() const {return hitbox*size;}
tools::POSf Player::get_pointer_hitbox() const {return pointer_hitbox*size;}

void Player::interact(__HAND_ACTION_ARGUMENTS)
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

void Player::main_hand_action(__HAND_ACTION_ARGUMENTS) {
    if(!__main_hand_action)
        return;
    if(std::abs(world.get_height(this->get_pos()) - world.get_height(pointer_pos)) > ascendable_height)
        return;
    __main_hand_action(pointer_pos,world,find_collided_entites_by_pointer);
}
void Player::off_hand_action(__HAND_ACTION_ARGUMENTS) {
    if(!__off_hand_action)
        return;
    if(std::abs(world.get_height(this->get_pos()) - world.get_height(pointer_pos)) > ascendable_height)
        return;
    __off_hand_action(pointer_pos,world,find_collided_entites_by_pointer);
}

#undef __HAND_ACTION_ARGUMENTS