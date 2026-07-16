#include "interactableEntity.hpp"

InteractableEntity::InteractableEntity(const tools::POSf& pos, tools::POSf size)
    : Entity(pos, size)
    , __is_interacted(false)
{} 

void InteractableEntity::update(const WindowManager& window_manager, const WorldManager& world_manager)
{
    if(__is_interacted)
    {
        __is_interacted = false;
        return;
    }
}

bool InteractableEntity::is_interacted() const {return __is_interacted;}
void InteractableEntity::set_interacted_state(bool state) {__is_interacted = state;}