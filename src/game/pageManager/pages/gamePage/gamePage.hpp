#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/worldManager.hpp"
#include "game/pageManager/pages/page.hpp"

class GamePage : public Page
{
    private :
        WorldManager world_manager;
    public :
        GamePage(const FileManager& file_manager);
        virtual PageSignal proceed_page(FileManager& file_manager, sf::RenderWindow& window) override;
        constexpr virtual Name get_name() const override;
};
