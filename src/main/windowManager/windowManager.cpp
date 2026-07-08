#include "main/windowManager/windowManager.hpp"
#include "main/windowManager/tick.hpp"
#include "resourceManager/fileManager/imageData/imageDatas.hpp"
#include "tools/cast.hpp"

WindowManager::ScreenSizeType WindowManager::screen_size;
WindowManager::ScreenSizeType WindowManager::screen_center;

WindowManager::WindowManager(std::string&& name)
    : videoMode(sf::VideoMode::getDesktopMode())
    , window(videoMode, std::move(name))
    , capture_sprite(sf::Sprite(capture_texture))
{
    screen_size = tools::POSf(videoMode.size.x, videoMode.size.x / ratio);
    screen_center = screen_size / 2.f;
    
    view = sf::View(sf::FloatRect({0.f, 0.f}, {screen_size.x, screen_size.y}));
    view.setViewport(get_resized_viewport(window.getSize()));
    set_view();
    window.setFramerateLimit(Tick::FRAMERATE);
}

WindowManager::ScreenSizeType WindowManager::get_screen_size() {return screen_size;}
WindowManager::ScreenSizeType WindowManager::get_screen_center() {return screen_center;}

float WindowManager::get_scale(const Camera& camera)
{
    const float base_width = 1470.f;
    const float current_width = WindowManager::get_screen_size().x;
    return (current_width / base_width) * (6.5 / camera.get_altitude());
}
tools::POSf WindowManager::get_pixel_world_origin(const Camera& camera)
{
    return (WindowManager::get_screen_size() / 2.f) - (camera.get_pos() * WorldImageData::TILE_SIZE.get(WindowManager::get_scale(camera)));
}
tools::POSs WindowManager::get_pixel_world_size(const Camera& camera)
{
    const auto screen_size = WindowManager::get_screen_size();
    const auto scaled_tile_size = WorldImageData::TILE_SIZE.get(WindowManager::get_scale(camera));
    return tools::POSi(ceil(screen_size.x/scaled_tile_size.x),ceil(screen_size.y/scaled_tile_size.y));
}
tools::POSf WindowManager::pixel_pos_to_world_pos(const tools::POSf& pixel_pos, const Camera& camera)
{
    const auto world_origin_in_screen = get_pixel_world_origin(camera);
    const auto scaled_tile_size = WorldImageData::TILE_SIZE.get(WindowManager::get_scale(camera));
    return (pixel_pos - world_origin_in_screen) / scaled_tile_size;
}
tools::POSf WindowManager::world_pos_to_pixel_pos(const tools::POSf& world_pos, const Camera& camera)
{
    const auto world_origin_in_screen = get_pixel_world_origin(camera);
    const auto scaled_tile_size = WorldImageData::TILE_SIZE.get(WindowManager::get_scale(camera));
    return world_origin_in_screen + world_pos * scaled_tile_size;
}
std::pair<tools::POSf,tools::POSf> WindowManager::get_displayed_world_range(const World& world, const Camera& camera)
{
    const auto scaled_tile_size = WorldImageData::TILE_SIZE.get(get_scale(camera));
    const auto pixel_world_size = get_pixel_world_size(camera);
    
    const auto camera_pos = camera.get_pos();
    const auto world_origin_in_screen = get_pixel_world_origin(camera);

    const auto world_size = world.get_size();

    auto start = tools::POSf(
        std::fmax(0, tools::CASTf(floor(camera_pos.x - pixel_world_size.x / 2.f))),
        std::fmax(0, tools::CASTf(floor(camera_pos.y - pixel_world_size.y / 2.f)))
    );
    auto end = tools::POSf(
        std::fmin(tools::CASTf(world_size.c), tools::CASTf(ceil(camera_pos.x + pixel_world_size.x / 2.f))),
        std::fmin(tools::CASTi(world_size.r), tools::CASTi(ceil(camera_pos.y + pixel_world_size.y / 2.f)))
    );
    return {start,end};
}


sf::FloatRect WindowManager::get_resized_viewport(const sf::Vector2u& window_size)
{
    const float windowRatio = tools::CASTf(window_size.x) / fmax(tools::CASTf(window_size.y), 1.0f);

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

sf::FloatRect WindowManager::get_resized_window(const sf::Event::Resized* resize)
{
    if(!resize)
        throw std::runtime_error("No resize event! in windowResize()");

    return get_resized_viewport(resize->size);
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


