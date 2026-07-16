#pragma once
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "main/windowManager/windowManager.hpp"

class WorldManager;

class Pointer : public Entity
{
    private :
        bool __focus;
    public :
        Pointer();

        void focus(bool value);
        bool is_focusing() const;
        
        virtual EntityName get_name() const override { return EntityName::pointer; }
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override;
};