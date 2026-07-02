#include "main/windowManager/windowManager.hpp"
#include "tools/cast.hpp"

WindowManager::WindowManager(std::string&& name)
    : videoMode(sf::VideoMode::getDesktopMode())
    , window(videoMode, std::move(name))
    , screen_size(tools::POSf(videoMode.size.x,videoMode.size.y))
    , screen_center(screen_size/2)
    , ratio(screen_size.x/fmax(screen_size.y,1))
    , capture_sprite(sf::Sprite(capture_texture))
{
    view = sf::View(sf::FloatRect({0.f, 0.f}, {screen_size.x, screen_size.y}));
    set_view();

    set_frame_rate_limit(120);
}

WindowManager::ScreenSizeType WindowManager::get_screen_size() {return screen_size;}
WindowManager::ScreenSizeType WindowManager::get_screen_center() {return screen_center;}


sf::FloatRect WindowManager::get_resized_window(const sf::Event::Resized* resize)
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

const decltype(WindowManager::window)& WindowManager::get_window() const
{
    return window;
}
decltype(WindowManager::window)& WindowManager::get_window()
{
    return window;
}

void WindowManager::capture_window()
{
    capture_texture = sf::Texture(window.getSize()); 
    capture_texture.update(window);
    capture_sprite.setTexture(capture_texture, true);
}
decltype(WindowManager::capture_sprite) WindowManager::get_capture_sprite() const
{
    return capture_sprite;
}


void WindowManager::clear(sf::Color color)
{
    window.clear(color);
}

void WindowManager::close()
{
    window.close();
}

bool WindowManager::is_open() const {return window.isOpen();}

void WindowManager::display()
{
    window.display();
}

void WindowManager::set_frame_rate_limit(unsigned int frameRate)
{
    window.setFramerateLimit(frameRate);
}

std::optional<sf::Event> WindowManager::poll_event()
{
    return window.pollEvent();
}

void WindowManager::resize_window(const std::optional<sf::Event>& event)
{
    if(!event)
        return;
    if(const auto* resized = event->getIf<sf::Event::Resized>())
        view.setViewport(get_resized_window(resized));
}

void WindowManager::set_view()
{
    window.setView(view);
}


