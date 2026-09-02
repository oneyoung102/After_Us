#include "player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

Player::Player(const tools::POSf& pos)
    : Creature(pos, 0.9f, 0.02, 1, 100, 100, 10, 10, 0.4f, 10.0f)
    , thirst(max_thirst/2)
    , hungry(max_hungry/2)
{
    set_reach(0.75);
    set_main_hand_actions({__CAST_HAND_ACTION(interact), __CAST_HAND_ACTION(sip)});
}

void Player::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    Creature::update(window_manager, world_manager);
}

tools::POSf Player::get_hitbox() const {return hitbox*size;}
tools::POSf Player::get_pointer_hitbox() const {return pointer_hitbox*size;}

void Player::add_hungry(int value){hungry = std::max(0, std::min(max_hungry, hungry + value));}
int Player::get_hungry() const {return hungry;}
void Player::add_thirst(int value){thirst = std::max(0, std::min(max_thirst, thirst + value));}
int Player::get_thirst() const {return thirst;}


//////////////////////////////////////////////////////////////////////////////////////////////////

void Player::set_reach(float reach)
{
    if(reach < 0)
        throw std::runtime_error("reach of player must be positive");
    this->reach = reach;
}
float Player::get_reach() const {return reach;}

bool Player::can_reach(const tools::POSf& pointer_pos, const World& world) const
{
    return std::abs(world[this->get_pos()].height - world[pointer_pos].height) <= ascendable_height;
}


bool Player::interact(__HAND_ACTION_ARGUMENTS)
{
    auto collided_entites = find_collided_entites_by_pointer();
    if(collided_entites.empty())
        return false;

    std::shared_ptr<InteractableEntity> entity;
    for(auto& collided_entity : collided_entites)
        if(auto interactable_entity = std::dynamic_pointer_cast<InteractableEntity>(collided_entity))
        {
            if(!entity || entity->get_pos().square_size() > interactable_entity->get_pos().square_size())
                entity = interactable_entity;
        }
    if(!entity)
        return false;
    entity->set_interacted_state(true);
    return true;
}
bool Player::sip(__HAND_ACTION_ARGUMENTS)
{
    if(world[pointer_pos].name != Tile::TileName::WATER)
        return false;   
    add_thirst(-100);
    return true;
}


void Player::set_main_hand_actions(std::vector<HAND_ACTION_TYPE>&& main_hand_actions)
{
    this->main_hand_actions = std::move(main_hand_actions);
}
void Player::set_off_hand_actions(std::vector<HAND_ACTION_TYPE>&& off_hand_actions)
{
    this->off_hand_actions = std::move(off_hand_actions);
}

bool Player::main_hand_action(__HAND_ACTION_ARGUMENTS) {
    if(main_hand_actions.empty())
        return false;
    if(!can_reach(pointer_pos, world))
        return false;
    for(auto& main_hand_action : main_hand_actions)
        if(main_hand_action(pointer_pos,world,find_collided_entites_by_pointer))
            return true;
    return false;
}
bool Player::off_hand_action(__HAND_ACTION_ARGUMENTS) {
    if(off_hand_actions.empty())
        return false;
    if(!can_reach(pointer_pos, world))
        return false;
    for(auto& off_hand_action : off_hand_actions)
        if(off_hand_action(pointer_pos,world,find_collided_entites_by_pointer))
            return true;
    return false;
}

#undef __CAST_HAND_ACTION
#undef __HAND_ACTION_ARGUMENTS