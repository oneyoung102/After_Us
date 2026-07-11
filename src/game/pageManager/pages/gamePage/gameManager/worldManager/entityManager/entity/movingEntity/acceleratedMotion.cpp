#include "acceleratedMotion.hpp"
#include "tools/dir.hpp"
#include <cmath>


AcceleratedMotion::AcceleratedMotion(float speed)
    : speed(speed)
{
    if(this->speed <= 0)
        throw std::runtime_error("acceleration must be positive");
}
        
void AcceleratedMotion::accel()
{
    if(directions.empty())
    {
        if(power.x > 0)      power.x = fmax(0.f,power.x-POWER_LESS);
        else if(power.x < 0) power.x = fmin(0.f,power.x+POWER_LESS);

        if(power.y > 0)      power.y = fmax(0.f,power.y-POWER_LESS);
        else if(power.y < 0) power.y = fmin(0.f,power.y+POWER_LESS);

        return;
    }

    while(!directions.empty())
    {
        power += tools::POSf(tools::DIR[directions.front()])*POWER_GRADIANCE;
        directions.pop();
    }
    const float size = std::sqrt(power.x*power.x + power.y*power.y);
    if(size > MAX_POWER)
        power = std::move(power*MAX_POWER/size);
}
void AcceleratedMotion::add_direction(tools::Direction dir) {directions.push(dir);}

tools::POSf AcceleratedMotion::get_vector() const {return power*speed;}

void AcceleratedMotion::stop() {power = tools::POSf();}

bool AcceleratedMotion::is_moving() const {return power.x != 0.f || power.y != 0.f;}

void AcceleratedMotion::set_speed(float speed) {this->speed = fmax(0,speed);}
float AcceleratedMotion::get_speed() const {return speed;}
