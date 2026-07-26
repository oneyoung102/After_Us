#include "fallenItem.hpp"

FallenItem::FallenItem(const tools::POSf& pos, ItemName item_name)
    : InteractableEntity(pos, 0.25f)
    , item_name(item_name)
{   
}

tools::POSf FallenItem::get_hitbox() const {return hitbox*size;}
tools::POSf FallenItem::get_pointer_hitbox() const {return pointer_hitbox*size;}

FallenItem::ItemName FallenItem::get_item_name() const
{
    return item_name;
}

    