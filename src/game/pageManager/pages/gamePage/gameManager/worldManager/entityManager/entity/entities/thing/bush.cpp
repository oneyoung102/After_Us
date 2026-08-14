#include "bush.hpp"

Bush::Bush(const tools::POSf& pos, float size, BushName bush_name)
    : Thing(pos, size*0.5) // 기본 이미지 크기가 크기 때문에 0.5배
    , bush_name(bush_name)
{}

tools::POSf Bush::get_hitbox() const {return hitbox[(size_t)bush_name]*size;}
tools::POSf Bush::get_pointer_hitbox() const {return pointer_hitbox[(size_t)bush_name]*size;}