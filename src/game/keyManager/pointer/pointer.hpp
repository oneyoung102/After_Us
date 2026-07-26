#pragma once
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "main/windowManager/windowManager.hpp"

class WorldManager;

class Pointer : public Entity
{
    private :
        static constexpr tools::POSf hitbox = {0.0, 0.0};
        static constexpr tools::POSf pointer_hitbox = {1, 1};

        bool __focus;
    public :
        Pointer();

        void focus(bool value);
        bool is_focusing() const;
        
        virtual EntityName get_name() const override { return EntityName::pointer; }
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;
        virtual bool is_collided(const Entity& entity, const World& world) const override;
        
        virtual tools::POSf get_hitbox() const override;
        virtual tools::POSf get_pointer_hitbox() const override;
};