#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"

class Chunk
{
    private :
        using ENTITY_LIST_TYPE = std::vector<std::shared_ptr<Entity>>; //y좌표 기준 오름차순 정렬(insert sort)
        
        ENTITY_LIST_TYPE static_entities;
        ENTITY_LIST_TYPE dynamic_entities;
    public :
        constexpr static unsigned int CHUNK_SIZE = 16; //청크는 정사각형

        Entity& get_static_entity(size_t idx);
        Entity& get_dynamic_entity(size_t idx);
        const Entity& get_static_entity(size_t idx) const;
        const Entity& get_dynamic_entity(size_t idx) const;

        std::shared_ptr<Entity> get_static_entity_ptr(size_t idx);
        std::shared_ptr<Entity> get_dynamic_entity_ptr(size_t idx);
        std::shared_ptr<const Entity> get_static_entity_ptr(size_t idx) const;
        std::shared_ptr<const Entity> get_dynamic_entity_ptr(size_t idx) const;

        size_t get_static_entities_size() const;
        size_t get_dynamic_entities_size() const;

        void insert(std::shared_ptr<Entity> entity);

        void erase(const std::shared_ptr<const Entity>& entity);

        std::shared_ptr<Entity> find_static_entity(const std::function<bool(const Entity&, const Entity&)>& condition);
        std::shared_ptr<Entity> find_dynamic_entity(const std::function<bool(const Entity&, const Entity&)>& condition);
        std::vector<std::shared_ptr<Entity>> find_static_entities(const std::function<bool(const Entity&)>& condition);
        std::vector<std::shared_ptr<Entity>> find_dynamic_entities(const std::function<bool(const Entity&)>& condition);
};