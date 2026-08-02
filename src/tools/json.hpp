#include "resourceManager/fileManager/fileManager.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace tools {

    template<typename T>
    void save_to_json(const T& value, std::string&& filename)
    {
        filename = FileManager::get_folder_path("Data")/filename;
        nlohmann::json j = value; 

        std::ofstream out_file(filename);
        if (out_file.is_open())
        {
            out_file << j.dump(1); 
            out_file.close();
            std::cout << filename << " 저장 완료!\n";
        }
        else
            std::cerr << "저장할 파일을 열 수 없습니다!\n";
    }

    template<typename T>
    T load_from_json(std::string&& filename)
    {
        filename = FileManager::get_folder_path("Data")/filename;
        T value;
        std::ifstream in_file(filename);
        
        if (in_file.is_open())
        {
            nlohmann::json j;
            in_file >> j;
            in_file.close();
            value = j.get<T>(); 
            std::cout << filename << " 불러오기 완료!\n";
        }
        else
            std::cerr << "불러올 파일을 찾을 수 없습니다!\n";
        
        return value;
    }
}
