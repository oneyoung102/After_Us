#include "main/windowManager/windowManager.hpp"
#include "tools/cast.hpp"

WindowManager::WindowManager(std::string&& name)
    : videoMode(sf::VideoMode::getDesktopMode())
    , window(videoMode, std::move(name))
    , screenSize(tools::POSf(videoMode.size.x,videoMode.size.y))
    , screenCenter(screenSize/2)
    , ratio(screenSize.x/fmax(screenSize.y,1))
    , captureSprite(sf::Sprite(captureTexture))
{
    view = sf::View(sf::FloatRect({0.f, 0.f}, {screenSize.x, screenSize.y}));
    setView();

    setFrameRateLimit(120);
}

WindowManager::SCREEN_SIZE_TYPE WindowManager::getScreenSize() {return screenSize;}
WindowManager::SCREEN_SIZE_TYPE WindowManager:: getScreenCenter() {return screenCenter;}

const sf::Event::Resized* WindowManager::getResizeEvent(const sf::Event& event)
{
    return event.getIf<sf::Event::Resized>();
}

sf::FloatRect WindowManager::getResizedWindow(const sf::Event::Resized* resize)
{
    if(!resize)
        throw std::runtime_error("No resize event! in windowResize()");

    const float windowRatio = tools::CASTf(resize->size.x) / fmax(tools::CASTf(resize->size.y),1);

    float viewportWidth = 1.f, viewportHeight = 1.f, viewportX = 0.f, viewportY = 0.f;

    if(windowRatio > ratio)
    {
        viewportWidth = ratio / windowRatio;
        viewportX = (1.f - viewportWidth) / 2.f;
    }
    else if(windowRatio < ratio)
    {
        viewportHeight = windowRatio / ratio;
        viewportY = (1.f - viewportHeight) / 2.f;
    }
    return sf::FloatRect({viewportX, viewportY}, {viewportWidth, viewportHeight});
}

const decltype(WindowManager::window)& WindowManager::getWindow() const
{
    return window;
}
decltype(WindowManager::window)& WindowManager::getWindow()
{
    return window;
}

void WindowManager::captureWindow()
{
    captureTexture = sf::Texture(window.getSize()); 
    captureTexture.update(window);
    captureSprite.setTexture(captureTexture, true);
}
decltype(WindowManager::captureSprite) WindowManager::getCaptureSprite() const
{
    return captureSprite;
}


void WindowManager::clear(sf::Color color)
{
    window.clear(color);
}

void WindowManager::close()
{
    window.close();
}

bool WindowManager::isOpen() const {return window.isOpen();}

void WindowManager::display()
{
    window.display();
}

void WindowManager::setFrameRateLimit(unsigned int frameRate)
{
    window.setFramerateLimit(frameRate);
}

std::optional<sf::Event> WindowManager::pollEvent()
{
    return window.pollEvent();
}

void WindowManager::resizeWindow(const sf::Event& event)
{
    if(const auto* resized = getResizeEvent(event))
        view.setViewport(getResizedWindow(resized));
}

void WindowManager::setView()
{
    window.setView(view);
}


