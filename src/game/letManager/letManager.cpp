#include <SFML/Graphics.hpp>

#include "game/letManager/letManager.hpp"

using namespace std;
using namespace sf;

LetManager::LetManager()
{
    clear();
}  

void LetManager::act_keyboard_let(const optional<Event>& event)
{
    if(!event)
        return;
    if(auto* key = event->getIf<Event::KeyPressed>())
    {
        if(key->code == sf::Keyboard::Key::Unknown)
            return;
        auto& func = key_allot[static_cast<size_t>(key->code)];
        if(func)
            func();
    }
}
void LetManager::allot_key(Keyboard::Key key, function<void()>&& func){key_allot[static_cast<size_t>(key)] = std::move(func);}
void LetManager::clear()
{
    key_allot.fill(nullptr);
}
void LetManager::clear(Keyboard::Key key)
{
    key_allot[static_cast<size_t>(key)] = nullptr;
}