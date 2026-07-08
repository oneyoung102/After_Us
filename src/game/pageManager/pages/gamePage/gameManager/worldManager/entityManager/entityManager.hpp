#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "game/letManager/letManager.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/player/player.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Chunk
{
    private :
        using ENTITY_LIST_TYPE = std::vector<std::shared_ptr<Entity>>; //y좌표 기준 오름차순 정렬(insert sort)
        
        ENTITY_LIST_TYPE static_entities;
        ENTITY_LIST_TYPE dynamic_entities;
    public :
        constexpr static unsigned int CHUNK_SIZE = 16; //청크는 정사각형

        Entity& get_static_entity(size_t idx) {return *static_entities[idx];}
        Entity& get_dynamic_entity(size_t idx) {return *dynamic_entities[idx];}
        const Entity& get_static_entity(size_t idx) const {return *static_entities[idx];}
        const Entity& get_dynamic_entity(size_t idx) const {return *dynamic_entities[idx];}

        std::shared_ptr<Entity> get_static_entity_ptr(size_t idx) {return static_entities[idx];}
        std::shared_ptr<Entity> get_dynamic_entity_ptr(size_t idx) {return dynamic_entities[idx];}
        std::shared_ptr<const Entity> get_static_entity_ptr(size_t idx) const {return static_entities[idx];}
        std::shared_ptr<const Entity> get_dynamic_entity_ptr(size_t idx) const {return dynamic_entities[idx];}

        size_t get_static_entities_size() const {return static_entities.size();}
        size_t get_dynamic_entities_size() const {return dynamic_entities.size();}

        void insert(std::shared_ptr<Entity> entity)
        {
            auto* entities = &static_entities;
            if(entity->is_dynamic_entity())
                entities = &dynamic_entities;

            auto pos = entity->get_pos();
            auto it = std::lower_bound(entities->begin(), entities->end(), pos.y, [](const std::shared_ptr<Entity>& a, float val){
                return a->get_pos().y < val;
            });
            entities->insert(it, std::move(entity));
        }

        void erase(const std::shared_ptr<const Entity>& entity, std::optional<float> search_y = std::nullopt) 
        {
            auto* entities = &static_entities;
            if(entity->is_dynamic_entity())
                entities = &dynamic_entities;
            
            float target_y = search_y.value_or(entity->get_pos().y);
            auto it = std::lower_bound(entities->begin(), entities->end(), target_y, [](const std::shared_ptr<Entity>& a, float val){
                return a->get_pos().y < val;
            }); 
            entities->erase(std::remove(it, entities->end(), entity), entities->end());
        }
};

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


        Chunk& get_chunk(const tools::POSs& pos);
        const Chunk& get_chunk(const tools::POSs& pos) const;
        tools::POSs get_chunks_size() const;

        void register_entity(std::shared_ptr<Entity> entity);
        void unregister_entity(const std::shared_ptr<const Entity>& entity);
        void move_entity(const tools::POSf& prev_pos, const std::shared_ptr<Entity>& entity);

        std::pair<tools::POSs,tools::POSs> get_update_chunk_range(const World& world, const Camera& camera) const;

        void update(const WorldManager& world_manager);


        void allot_player_keys(LetManager& let_manager);

        Player& get_player();
        const Player& get_player() const;
        std::shared_ptr<Player> get_player_ptr();
        std::shared_ptr<const Player> get_player_ptr() const;
};
