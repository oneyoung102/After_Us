#include <SFML/Graphics.hpp>

#include <mach-o/dyld.h>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>

#include "resourceManager/fileManager/fileManager.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include "tools/cast.hpp"


using namespace sf;
using namespace std;
using namespace tools;
namespace fs = std::filesystem;

fs::path FileManager::get_executable_path() 
{
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
        throw runtime_error("Unable to get executable path");
    return fs::canonical(path);
}
fs::path FileManager::get_folder_path(const string& folder)
{
    return get_executable_path().parent_path().parent_path() / folder;
}

std::vector<sf::Texture> FileManager::get_all_texture()
{
    std::vector<sf::Texture> textures;
    const fs::path imgPath = get_folder_path("Resources/assets")/"image";
    vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(imgPath))
        if (entry.path().extension() == ".png")
            files.push_back(entry.path());
    sort(files.begin(), files.end());
    for (const auto& path : files)
    {
        Texture texture;
        if (!texture.loadFromFile(path.string()))
            throw runtime_error("Unable to load image");
        textures.push_back(texture);
    }
    return textures;
}
void FileManager::get_font()
{
    const fs::path fontPath = get_folder_path("Resources/assets")/"font/puyo_font.ttf";
    if (!font.openFromFile(fontPath.string()))
        throw runtime_error("Unable to load image");
}

void FileManager::get_all_sound()
{
    const fs::path soundPath = get_folder_path("Resources/assets")/"sound";
    vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(soundPath))
        if (entry.path().extension() == ".mp3")
            files.push_back(entry.path());
    sort(files.begin(), files.end());
    for (const auto& path : files)
    {
        SoundBuffer buffer;
        if (!buffer.loadFromFile(path.string()))
            throw runtime_error("Unable to load sound");
        buffers.push_back(buffer);
    }
}

void FileManager::get_all_music_path()
{
    const fs::path soundPath = get_folder_path("Resources/assets")/"music";
    for (const auto& entry : fs::directory_iterator(soundPath))
        if (entry.path().extension() == ".mp3")
            musics.push_back(entry.path());
    sort(musics.begin(), musics.end());
}

FileManager::FileManager()
    : gen(random_device{}())
    , image_datas(ImageDatas(get_all_texture()))
{
    //get_font();
    get_all_sound();
    get_all_music_path();
}

const ImageDatas& FileManager::get_image_datas() const {return image_datas;}

const Font& FileManager::get_font() const {return font;}
sf::SoundBuffer& FileManager::get_buffer(FileManager::Sound name){return buffers[CASTs(name)];}
const fs::path& FileManager::get_music(FileManager::Music name) const {return musics[CASTs(name)];}
// const fs::path& fileManager::get_random_music()
// {
//     uniform_int_distribution<> dist(CASTi(Music::game_music1), CASTi(Music::game_music11));
//     return musics[dist(gen)];
// }
