#include <SFML/Graphics.hpp>

#include "game/letManager/letManager.hpp"

using namespace std;
using namespace sf;

LetManager::LetManager()
{
    clear();
}  

void LetManager::actKeyboardLet(const optional<Event>& event)
{
    if(!event)
        return;
    if(auto* key = event->getIf<Event::KeyPressed>())
    {
        if(key->code == sf::Keyboard::Key::Unknown)
            return;
        auto& func = keyAllot[static_cast<size_t>(key->code)];
        if(func)
            func();
    }
}
void LetManager::allotKey(Keyboard::Key key, function<void()>&& func){keyAllot[static_cast<size_t>(key)] = std::move(func);}
void LetManager::clear()
{
    keyAllot.fill(nullptr);
}
void LetManager::clear(Keyboard::Key key)
{
    keyAllot[static_cast<size_t>(key)] = nullptr;
}