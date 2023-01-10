#include "entity.hpp"

Entity::~Entity() {}; // Destructor from a child child class also calls destructor from super class (must be defined)

sf::Sprite Entity::getSprite(){
    return sprite;
}