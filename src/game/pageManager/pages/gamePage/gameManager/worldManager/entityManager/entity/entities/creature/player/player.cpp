#include "player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

Player::Player(const tools::POSf& pos)
    : Creature(pos, {0.4,0.4}, DEFAULT_SPEED, 1, 100, 100, 10, 10, 0.4, 10.0)
{
    set_reach(0.75);
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
