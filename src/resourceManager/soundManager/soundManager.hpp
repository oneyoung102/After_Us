#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

class SoundManager
{
    private :
        sf::Music music;
        std::vector<std::unique_ptr<sf::Sound>> sounds;
    public :
        SoundManager();
        void manageSounds();
        void playSound(sf::SoundBuffer& buffer);
        void playMusic(const std::filesystem::path& path);
        bool isEmpty();
        void clearBack();
        bool backIsAlive();
};