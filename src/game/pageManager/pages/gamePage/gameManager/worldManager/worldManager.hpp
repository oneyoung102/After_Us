#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/world.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entityManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/camera/camera.hpp"

class WorldManager
{
    private :
        constexpr static int ONE_DAY = 60*60*24;
        Tick time;
        World world;
        EntityManager entity_manager;
        Camera camera;
    public :
        WorldManager(Tick time, Camera&& camera);

        const World& get_world() const;
        World& get_world();

        const Camera& get_camera() const;
        Camera& get_camera(); 

        const EntityManager& get_entity_manager() const;
        EntityManager& get_entity_manager();

        void update(const WindowManager& window_manager);
};