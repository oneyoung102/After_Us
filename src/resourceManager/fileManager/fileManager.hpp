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

        void get_all_texture();
        void get_all_sprite();
        void get_font();
        void get_all_sound();
        void get_all_music_path();
        
    public :
        FileManager();
        static std::filesystem::path get_executable_path();
        static std::filesystem::path get_folder_path(const std::string& folder);
        
        enum class Image{//이미지 명
            world_asset,
        };
        enum class Sound{//사운드 명
        };
        enum class Music{//음악 명

        };
        sf::Sprite get_sprite(Image name) const;
        const sf::Font& get_font() const;
        sf::SoundBuffer& get_buffer(Sound name);
        const std::filesystem::path& get_music(Music name) const;
        const std::filesystem::path& get_random_music() = delete;
};