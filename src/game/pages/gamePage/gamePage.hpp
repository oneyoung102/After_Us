#pragma once

#include "game/pages/gamePage/gameManager/world/worldManager.hpp"
#include "game/pages/page.hpp"
#include "main/windowManager/windowManager.hpp"

class GamePage : public Page
{
    private :
        WorldManager world_manager;
    public :
        GamePage(const FileManager& file_manager, WindowManager::ScreenSizeType screen_size);
        virtual PageSignal proceed_page(FileManager& file_manager, sf::RenderWindow& window) override;
        constexpr virtual Name get_name() const override;
};
