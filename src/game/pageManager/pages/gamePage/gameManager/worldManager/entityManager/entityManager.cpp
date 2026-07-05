#include "thingManager.hpp"
#include <cmath>

ThingManager::ThingManager(const World& world)
    : chunks(
        std::ceil(world.get_size().r / tools::CASTf(CHUNK_SIZE)),
        std::vector<ONE_CHUNK_TYPE>(std::ceil(world.get_size().c/tools::CASTf(CHUNK_SIZE)),
        ONE_CHUNK_TYPE(CHUNK_SIZE))
    )
{
    available_thing_codes.fill(Thing::UNREGISTERED+1);
}

void ThingManager::register_thing(std::shared_ptr<Thing>&& thing)
{
    if(thing->is_registered())
        throw std::runtime_error("thing is already registered");
    const int idx = tools::CASTs(thing->get_name());
    thing->set_thing_code(available_thing_codes[idx]++);

    const auto chunk_pos = get_chunk_pos(thing);
    const auto row_in_chunk = get_row_in_chunk(thing);
    chunks[chunk_pos.r][chunk_pos.c][row_in_chunk].push_back(std::move(thing));
}

void ThingManager::unregister_thing(std::shared_ptr<Thing> thing)
{
    if(!thing->is_registered())
        throw std::runtime_error("thing is not registered");
    const auto chunk_pos = get_chunk_pos(thing);
    const auto row_in_chunk = get_row_in_chunk(thing);

    auto& row = chunks[chunk_pos.r][chunk_pos.c][row_in_chunk];
    for(size_t i = 0 ; i < row.size() ;)
        if(!row[i] || row[i] == thing && row[i]->get_thing_code() == thing->get_thing_code())
        {
            std::swap(row[i], row.back());
            row.pop_back();
            break;
        }
        else
            i++;
}

void ThingManager::move_thing(const tools::POSf& prev_pos, std::shared_ptr<Thing> thing)
{

}