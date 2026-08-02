#include "tree.hpp"

Tree::Tree(const tools::POSf& pos, float size, TreeName tree_name)
    : Thing(pos, size)
    , tree_name(tree_name)
{}

tools::POSf Tree::get_hitbox() const {return hitbox[(size_t)tree_name]*size;}
tools::POSf Tree::get_pointer_hitbox() const {return pointer_hitbox[(size_t)tree_name]*size;}