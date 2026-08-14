#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/thing.hpp"
#include "tools/pos.hpp"
#include <array>

class Bush : public Thing
{
    public :
        enum class BushName
        {
            BUSH1,
            BUSH2,
            COUNT
        };
    private :
        BushName bush_name;

        static constexpr std::array<tools::POSf, (size_t)BushName::COUNT> hitbox = {
            tools::POSf(2, 1),
            tools::POSf(2.5, 1.2),
        };
        static constexpr std::array<tools::POSf, (size_t)BushName::COUNT> pointer_hitbox = {
            tools::POSf(3, 3),
            tools::POSf(4, 2),
        };

    public :
        Bush(const tools::POSf& pos = tools::POSf(), float size = 1.0, BushName bush_name = BushName::BUSH1);
        ~Bush() override = default;

        void update(const WindowManager& window_manager, const WorldManager& world_manager) override {}

        tools::POSf get_hitbox() const override;
        tools::POSf get_pointer_hitbox() const override;

        BushName get_bush_name() const {return bush_name;}  

        Entity::EntityName get_name() const override {return Entity::EntityName::bush;}  

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Bush, pos, size, entity_code, bush_name);
};

NLOHMANN_JSON_SERIALIZE_ENUM(Bush::BushName, {
    {Bush::BushName::BUSH1, "BUSH1"},
    {Bush::BushName::BUSH2, "BUSH2"},
    {Bush::BushName::COUNT, "COUNT"}
})