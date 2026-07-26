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
        
    private :
        static constexpr tools::POSf hitbox = {1.0, 0.5};
        static constexpr tools::POSf pointer_hitbox = {1.0, 1.0};
        
        const ItemName item_name;
    public :
    
        FallenItem(const tools::POSf& pos, ItemName item_name);

        virtual tools::POSf get_hitbox() const override;
        virtual tools::POSf get_pointer_hitbox() const override;

        ItemName get_item_name() const;

        virtual ~FallenItem() = default;
        virtual bool is_fallen_item() const override {return true;}
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}

        virtual Entity::EntityName get_name() const override {return EntityName::fallen_item;}
};