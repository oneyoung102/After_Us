#include "player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"

Player::Player(const tools::POSf& pos)
    : Creature(pos, 0.75, DEFAULT_SPEED, 1, 100, 100, 10, 10, 0.4, 10.0)
    , pointer(*this)
{
    set_reach(0.75);
}

void Player::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    pointer.update(window_manager, world_manager.get_camera());
    Creature::update(window_manager, world_manager);
}

const Pointer& Player::get_pointer() const {return pointer;}

void Player::set_reach(float reach)
{
    pointer.set_reach(reach);
}
float Player::get_reach() const {return pointer.get_reach();}
