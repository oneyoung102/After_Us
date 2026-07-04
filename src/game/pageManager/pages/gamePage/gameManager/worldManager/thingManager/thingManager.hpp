#pragma once

#include <vector>
#include <memory>
#include "game/pageManager/pages/gamePage/gameManager/worldManager/thingManager/thing/thing.hpp"
#include "tools/cast.hpp"

class ThingManager
{
    public:
        constexpr static unsigned int CHUNK_SIZE = 16; //청크는 정사각형
        using ONE_ROW_TYPE = std::vector<std::shared_ptr<Thing>>;
        using ONE_CHUNK_TYPE = std::vector<ONE_ROW_TYPE>; // 16 rows per chunk
        using CHUNCKS_TYPE = std::vector<std::vector<ONE_CHUNK_TYPE>>;

    private:
        std::array<Thing::THING_CODE, tools::CASTs(Thing::ThingName::COUNT)> available_thing_codes;

        CHUNCKS_TYPE chunks;
    public:
        ThingManager(const World& world);
        
        static inline tools::POSs get_chunk_pos(tools::POSf&& pos) {return tools::POSs(pos) / CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const tools::POSf& pos) {return tools::POSs(pos) / CHUNK_SIZE;}
        static inline tools::POSs get_chunk_pos(const std::shared_ptr<const Thing>& thing) {return tools::POSs(thing->get_pos()) / CHUNK_SIZE;}

        static inline size_t get_row_in_chunk(float row) {return tools::CASTs(row) % CHUNK_SIZE;}
        static inline size_t get_row_in_chunk(const std::shared_ptr<const Thing>& thing) {return tools::CASTs(thing->get_pos().r) % CHUNK_SIZE;}

        void register_thing(std::shared_ptr<Thing>&& thing);
        void unregister_thing(std::shared_ptr<Thing> thing);
        void move_thing(const tools::POSf& prev_pos, std::shared_ptr<Thing> thing);
};
