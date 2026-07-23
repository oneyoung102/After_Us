#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/interactableEntity/interactableEntity.hpp"

class FallenItem : public InteractableEntity
{
    public :
        enum class ItemName //나중에 아이템 클래스 만들면 옮길 거임 
        {
            apple,
            COUNT
        };
        const ItemName item_name;

        FallenItem(const tools::POSf& pos, ItemName item_name);

        ItemName get_item_name() const;

        virtual tools::POSf get_hitbox() const override;

        virtual ~FallenItem() = default;
        virtual bool is_fallen_item() const override {return true;}
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}

        virtual Entity::EntityName get_name() const override {return EntityName::fallen_item;}
};