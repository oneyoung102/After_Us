#pragma once

#include <vector>
#include <memory>
#include "game/letManager/letManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/fallenItem/fallenItem.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/thing/thing.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"
#include "tools/cast.hpp"

class WorldManager;

class EntityManager
{
    public:
        constexpr static unsigned int CHUNK_SIZE = 16; //청크는 정사각형
        using ONE_ROW_TYPE = std::vector<Entity*>;
        using ONE_CHUNK_TYPE = std::vector<ONE_ROW_TYPE>; // 16 rows per chunk
        using CHUNCKS_TYPE = std::vector<std::vector<ONE_CHUNK_TYPE>>;

    private:
        std::array<Entity::ENTITY_CODE, tools::CASTs(Entity::EntityName::COUNT)> available_entity_codes;

        std::vector<std::shared_ptr<FallenItem>> fallen_items;
        std::vector<std::shared_ptr<Thing>> things;
        std::vector<std::shared_ptr<Creature>> creatures;
        std::shared_ptr<Player> player;
        CHUNCKS_TYPE chunks;

    public:
        EntityManager(const World& world);
        
        static inline tools::POSs get_chunk_pos(tools::POSf&& pos) {return tools::POSs(pos) / CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const tools::POSf& pos) {return tools::POSs(pos) / CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const std::shared_ptr<const Entity>& entity) {return tools::POSs(entity->get_pos()) / CHUNK_SIZE;}

        static inline size_t get_row_in_chunk(float row) {return tools::CASTs(row) % CHUNK_SIZE;}
        static inline size_t get_row_in_chunk(const std::shared_ptr<const Entity>& entity) {return tools::CASTs(entity->get_pos().r) % CHUNK_SIZE;}

        ONE_CHUNK_TYPE& get_chunk(const tools::POSs& pos);
        const ONE_CHUNK_TYPE& get_chunk(const tools::POSs& pos) const;
        tools::POSs get_chunks_size() const;

        void register_entity(std::shared_ptr<Entity>&& entity);
        void unregister_entity(std::shared_ptr<Entity> entity);
        void move_entity(const tools::POSf& prev_pos, std::shared_ptr<Entity> entity);

        void update_players(const WorldManager& world_manager);
        void update_creatures(const WorldManager& world_manager);
        void update_fallen_items(const WorldManager& world_manager);
        void update_things(const WorldManager& world_manager);

        void allot_player_keys(LetManager& let_manager);
        std::shared_ptr<Player> get_player();
};
