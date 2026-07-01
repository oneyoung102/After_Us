#include "game/pages/gamePage/gamePage.hpp"
#include "game/pageManager/pageSignal.hpp"
#include "resourceManager/fileManager/fileManager.hpp"
#include "resourceManager/printManager/printObject/printWorld.hpp"

GamePage::GamePage(const FileManager& fileManager, WindowManager::SCREEN_SIZE_TYPE screenSize)
    : worldSize(tools::POSf(ceil(screenSize.x/imageConstant::BLOCK_SIZE.x),ceil(screenSize.y/imageConstant::BLOCK_SIZE.y)))
    , world(WORLD_TYPE(worldSize.y,std::vector<imageConstant::BlockCode>(worldSize.x,imageConstant::BlockCode::GRASS_1)))
{
    printManager.addObject(std::make_unique<PrintWorld>(world,screenSize,fileManager.getSprite(FileManager::Image::worldAsset)));
}

PageSignal GamePage::proceedPage(FileManager& fileManager, sf::RenderWindow& window)
{
    PageSignal pageSignal;
    
    printManager.printObjects(window);

    return pageSignal;
}
constexpr GamePage::Name GamePage::getName() const {return Name::game;}
