#pragma once

#include "game/pages/page.hpp"
#include "main/windowManager/windowManager.hpp"
#include "resourceManager/printManager/imageConstant.hpp"
#include <vector>

class GamePage : public Page
{
    private :
        using WORLD_TYPE = std::vector<std::vector<imageConstant::BlockCode>>;
        const tools::POSf worldSize;
        WORLD_TYPE world;
    public :
        GamePage(const FileManager& fileManager, WindowManager::SCREEN_SIZE_TYPE screenSize);
        virtual PageSignal proceedPage(FileManager& fileManager, sf::RenderWindow& window) override;
        constexpr virtual Name getName() const override;
};
