#include "resourceManager/soundManager/soundManager.hpp"

#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

SoundManager::SoundManager(){}
void SoundManager::manageSounds()
{
    for(size_t i = 0 ; i < sounds.size() ; )
        if(sounds[i]->getStatus() == Sound::Status::Stopped)
        {
            std::swap(sounds[i], sounds.back());
            sounds.pop_back();
        }
        else
            ++i;
}
void SoundManager::playSound(SoundBuffer& buffer)
{
    sounds.push_back(make_unique<Sound>(buffer));
    sounds.back()->play();
}

void SoundManager::playMusic(const filesystem::path& path)
{
    music = Music(path);
    music.setLooping(true);
    music.play();
}

 bool SoundManager::isEmpty(){return sounds.empty();}

void SoundManager::clearBack()
{
    if(!sounds.empty())
        sounds.pop_back();
}
bool SoundManager::backIsAlive()
{
    return !sounds.empty()
        && sounds.back()->getStatus() == Sound::Status::Playing;
}