#include <SFML/Graphics.hpp>

#include "game/keyManager/keyboardManager.hpp"

using namespace std;
using namespace sf;

KeyboardManager::KeyboardManager()
{
    clear();
}  

bool KeyboardManager::is_valid_key(sf::Keyboard::Key key) const
{
    int val = static_cast<int>(key);
    return 0 <= val && val < KEY_MAX_AMOUNT;
}

void KeyboardManager::update(const optional<Event>& event)
{
    if(!event)
        return;
    if(event->is<Event::FocusLost>())
        remained_key_delay.fill(-1);
    else if(auto* key = event->getIf<Event::KeyPressed>())
    {
        if(is_valid_key(key->code))
            remained_key_delay[static_cast<size_t>(key->code)] = key_delay[static_cast<size_t>(key->code)];
    }
    else if(auto* key = event->getIf<Event::KeyReleased>())
        if(is_valid_key(key->code))
            --remained_key_delay[static_cast<size_t>(key->code)];
}
void KeyboardManager::act_key_event() //staet, event 구분 없애고 하나로 통일 후, 키별로 지연시간 설정 가능하게
{ 
    for(size_t i = 0; i < key_allot.size(); ++i)
        if(key_allot[i] && remained_key_delay[i] == key_delay[i])
            key_allot[i]();
}
void KeyboardManager::allot_key(Keyboard::Key key, function<void()>&& func, tools::Tick delay)
{
    if(delay < 0)
        delay = 0;
    if(is_valid_key(key))
    {
        key_allot[static_cast<size_t>(key)] = std::move(func);
        key_delay[static_cast<size_t>(key)] = delay;
        remained_key_delay[static_cast<size_t>(key)] = -1;
    }
}
void KeyboardManager::clear()
{
    key_allot.fill(nullptr);
    remained_key_delay.fill(-1);
    key_delay.fill(-1);
}
void KeyboardManager::clear(Keyboard::Key key)
{
    if(is_valid_key(key))
    {
        key_allot[static_cast<size_t>(key)] = nullptr;
        key_delay[static_cast<size_t>(key)] = -1;
        remained_key_delay[static_cast<size_t>(key)] = -1;
    }
}