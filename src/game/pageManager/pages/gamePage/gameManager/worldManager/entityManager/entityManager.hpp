#pragma once

#include <vector>
#include <memory>
#include "game/keyManager/keyboardManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/chunk/chunk.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"



class Camera;
class World;
class WorldManager;
class EntityManager
{
    public:
        using CHUNCKS_TYPE = std::vector<std::vector<Chunk>>;

    private:
        static constexpr int UPDATE_CHUNK_DIAMETER = 1;
        Entity::ENTITY_CODE available_entity_code;

        std::weak_ptr<Player> player;
        CHUNCKS_TYPE chunks;

    public:
        EntityManager(const World& world, std::vector<std::unique_ptr<Entity>>&& entities = {});
        
        static inline tools::POSs get_chunk_pos(tools::POSf&& pos) {return tools::POSs(pos) / Chunk::CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const tools::POSf& pos) {return tools::POSs(pos) / Chunk::CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const std::shared_ptr<const Entity>& entity) {return tools::POSs(entity->get_pos()) / Chunk::CHUNK_SIZE;}

        static inline tools::POSf get_relative_pos(tools::POSf&& pos) {return pos-get_chunk_pos(pos)*Chunk::CHUNK_SIZE;}
        static inline tools::POSf get_relative_pos(const tools::POSf& pos) {return pos-get_chunk_pos(pos)*Chunk::CHUNK_SIZE;}

        bool is_valid_chunk(const tools::POSi& chunk_pos) const;

        Chunk& get_chunk(const tools::POSs& pos);
        const Chunk& get_chunk(const tools::POSs& pos) const;
        tools::POSs get_chunks_size() const;

        void register_entity(std::shared_ptr<Entity> entity);
        void unregister_entity(const std::shared_ptr<const Entity>& entity);
        void reregister_entity(const tools::POSf& prev_pos, const std::shared_ptr<Entity>& entity);

        std::pair<tools::POSs,tools::POSs> get_update_chunk_range(const World& world, const Camera& camera) const;

        void update(const WindowManager& window_manager, const WorldManager& world_manager);

        std::vector<std::shared_ptr<Entity>> find_collided_dynamic_entities(const Entity& entity);
        bool test_collision(const Entity& entity);

        void allot_player_keys(KeyboardManager& keyboard_Manager);

        Player& get_player();
        const Player& get_player() const;
        std::shared_ptr<Player> get_player_ptr();
        std::shared_ptr<const Player> get_player_ptr() const;
};
