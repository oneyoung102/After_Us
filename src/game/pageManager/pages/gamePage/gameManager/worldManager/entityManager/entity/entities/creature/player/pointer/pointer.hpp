#pragma once
#include "main/windowManager/windowManager.hpp"

class WorldManager;

class Pointer : public Entity
{
    private :
        bool focus;
        float reach;
        const Entity& center;
    public :
        Pointer(const Entity& center);
        
        bool is_focusing() const;
        
        void set_reach(float reach);
        float get_reach() const;
        
        void update(const WindowManager& window_manager, const Camera& camera);
        tools::POSf get_center_pos() const;
        virtual EntityName get_name() const override { return EntityName::pointer; }
        virtual void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}
};