#include "shader.hpp"
#include "resourceManager/fileManager/fileManager.hpp"


Shader::Shader()
{
    if(!shader.loadFromFile(FileManager::get_folder_path("Data")/"brightness.txt", sf::Shader::Type::Fragment))
        throw std::runtime_error("file for shading doesn't exist");
    set_brightness();
}

float Shader::get_brightness_by_height(int curr_tile_height, int tile_height)
{
    const float gap = curr_tile_height-tile_height;
    if(-1 <= gap && gap <= 1)
        return 1-0.1*gap;
    return 1-0.2*(gap/abs(gap));
}

sf::Shader& Shader::operator*()
{
    return shader;
}

void Shader::set_brightness(float brightness)
{
    this->brightness = brightness;
    shader.setUniform("brightness",this->brightness);
}

float Shader::get_brightness() const {return brightness;}
