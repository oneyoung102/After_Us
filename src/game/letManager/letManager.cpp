#include <SFML/Graphics.hpp>

#include "game/letManager/letManager.hpp"

using namespace std;
using namespace sf;

LetManager::LetManager()
{
    clear();
}  

bool LetManager::is_valid_key(sf::Keyboard::Key key) const
{
    int val = static_cast<int>(key);
    return 0 <= val && val < KEY_MAX_AMOUNT;
}

void LetManager::act_event_let(const optional<Event>& event)
{
    if(!event)
        return;
    if(event->is<Event::FocusLost>())
        state_keys_pressed.fill(false);
    else if(auto* key = event->getIf<Event::KeyPressed>())
    {
        if(is_valid_key(key->code))
        {
            state_keys_pressed[static_cast<size_t>(key->code)] = true;

            auto& func = event_key_allot[static_cast<size_t>(key->code)];
            if(func)
                func();
        }
    }
    else if(auto* key = event->getIf<Event::KeyReleased>())
        if(is_valid_key(key->code))
            state_keys_pressed[static_cast<size_t>(key->code)] = false;
}
void LetManager::act_state_let()
{
    for(size_t i = 0; i < state_key_allot.size(); ++i)
        if(state_key_allot[i] && state_keys_pressed[i])
            state_key_allot[i]();
}
void LetManager::allot_state_key(Keyboard::Key key, function<void()>&& func)
{
    if(is_valid_key(key))
        state_key_allot[static_cast<size_t>(key)] = std::move(func);
}
void LetManager::allot_event_key(Keyboard::Key key, function<void()>&& func)
{
    if(is_valid_key(key))
        event_key_allot[static_cast<size_t>(key)] = std::move(func);
}
void LetManager::clear()
{
    state_key_allot.fill(nullptr);
    event_key_allot.fill(nullptr);
    state_keys_pressed.fill(false);
}
void LetManager::clear(Keyboard::Key key)
{
    if(is_valid_key(key))
    {
        state_key_allot[static_cast<size_t>(key)] = nullptr;
        event_key_allot[static_cast<size_t>(key)] = nullptr;
        state_keys_pressed[static_cast<size_t>(key)] = false;
    }
}