#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "game/pageManager/pages/page.hpp"
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
