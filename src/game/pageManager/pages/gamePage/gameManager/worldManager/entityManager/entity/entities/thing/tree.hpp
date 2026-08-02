#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/thing.hpp"
#include "tools/pos.hpp"
#include <array>

class Tree : public Thing
{
    public :
        enum class TreeName
        {
            TREE1,
            TREE2,
            TREE3,
            TREE4,
            TREE5,
            TREE6,
            TREE7,
            COUNT
        };
    private :
        TreeName tree_name;

        static constexpr std::array<tools::POSf, (size_t)TreeName::COUNT> hitbox = {
            tools::POSf(0.375, 0.1875),
            tools::POSf(0.25, 0.125),
            tools::POSf(0.375, 0.1875),
            tools::POSf(0.25, 0.125),
            tools::POSf(2.2, 1.1),
            tools::POSf(1.125, 0.5625),
            tools::POSf(0.9375, 0.46875)
        };
        static constexpr std::array<tools::POSf, (size_t)TreeName::COUNT> pointer_hitbox = {
            tools::POSf(0.375, 5),
            tools::POSf(0.25, 5),
            tools::POSf(0.375, 5),
            tools::POSf(0.25, 5),
            tools::POSf(2.2, 5),
            tools::POSf(1.125, 5),
            tools::POSf(0.9375, 5)
        };

    public :
        Tree(const tools::POSf& pos, float size = 1.0, TreeName tree_name = TreeName::TREE1);
        ~Tree() override = default;

        void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}

        tools::POSf get_hitbox() const override;
        tools::POSf get_pointer_hitbox() const override;

        TreeName get_tree_name() const {return tree_name;}  

        Entity::EntityName get_name() const override {return Entity::EntityName::tree;}  
};