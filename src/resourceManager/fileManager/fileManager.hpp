#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <filesystem>
#include <string>
#include <random>


class FileManager
{
    private : 
        std::vector<sf::Texture> textures;
        std::vector<sf::Sprite> sprites;
        std::vector<sf::SoundBuffer> buffers;
        std::vector<std::filesystem::path> musics;

        std::mt19937 gen;

        sf::Font font;

        void getAllTexture();
        void getAllSprite();
        void getFont();
        void getAllSound();
        void getAllMusicPath();
        
    public :
        FileManager();
        static std::filesystem::path getExecutablePath();
        static std::filesystem::path getFolderPath(const std::string& folder);
        
        enum class Image{//이미지 명
            worldAsset,
        };
        enum class Sound{//사운드 명
        };
        enum class Music{//음악 명

        };
        sf::Sprite getSprite(Image name) const;
        const sf::Font& getFont() const;
        sf::SoundBuffer& getBuffer(Sound name);
        const std::filesystem::path& getMusic(Music name) const;
        const std::filesystem::path& getRsandomMusic() = delete;
};