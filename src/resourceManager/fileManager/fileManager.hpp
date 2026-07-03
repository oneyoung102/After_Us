#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <filesystem>
#include <string>
#include <random>

#include "resourceManager/fileManager/imageData/imageDatas.hpp"

class FileManager
{
    public :
        enum class Sound{//사운드 명
        };
        enum class Music{//음악 명

        };
    private : 
        const ImageDatas image_datas;
        std::vector<sf::SoundBuffer> buffers;
        std::vector<std::filesystem::path> musics;//뮤직 데이터, 등등도 추가할 예정

        std::mt19937 gen;

        sf::Font font;

        std::vector<sf::Texture> get_all_texture();
        void get_font();
        void get_all_sound();
        void get_all_music_path();
        
    public :
        FileManager();
        static std::filesystem::path get_executable_path();
        static std::filesystem::path get_folder_path(const std::string& folder);
        
        const ImageDatas& get_image_datas() const;
        const sf::Font& get_font() const;
        sf::SoundBuffer& get_buffer(Sound name);
        const std::filesystem::path& get_music(Music name) const;
        const std::filesystem::path& get_random_music() = delete;
};