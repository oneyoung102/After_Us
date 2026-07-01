#include "main/windowResize/windowResize.hpp"
#include "tools/cast.hpp"

const sf::Event::Resized* getResizeEvent(const sf::Event& event)
{
    return event.getIf<sf::Event::Resized>();
}

sf::FloatRect windowResize(const sf::Event::Resized* resize, const float RATIO)
{
    if(!resize)
        throw std::runtime_error("No resize event! in windowResize()");

    const float windowWidth = tools::CASTf(resize->size.x);
    const float windowHeight = tools::CASTf(resize->size.y);
    const float windowRatio = windowWidth / windowHeight;

    float viewportWidth = 1.f, viewportHeight = 1.f, viewportX = 0.f, viewportY = 0.f;

    if(windowRatio > RATIO)
    {
        viewportWidth = RATIO / windowRatio;
        viewportX = (1.f - viewportWidth) / 2.f;
    }
    else if(windowRatio < RATIO)
    {
        viewportHeight = windowRatio / RATIO;
        viewportY = (1.f - viewportHeight) / 2.f;
    }
    return sf::FloatRect({viewportX, viewportY}, {viewportWidth, viewportHeight});
}