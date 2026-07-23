#include "fallenItem.hpp"

FallenItem::FallenItem(const tools::POSf& pos, ItemName item_name)
    : InteractableEntity(pos, 0.25f)
    , item_name(item_name)
{
}

tools::POSf FallenItem::get_hitbox() const {return tools::POSf(0.5f,0.5f)*size;}

FallenItem::ItemName FallenItem::get_item_name() const
{
    return item_name;
}

    