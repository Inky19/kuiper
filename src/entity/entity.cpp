#include "entity.hpp"

Entity::~Entity() {}; // Destructor from a child child class also calls destructor from super class (must be defined)

sf::Sprite Entity::getSprite(){
    return sprite;
}

/**
 * Set the entity and its sprite to stay in frame (the entity repear on the other side of the frame)
 * @param setPosHitbox Also set the hitbox in frame. Default is true.
 */
void Entity::setInFrame(bool setPosHitbox){
    sf::Vector2i ori = (*frame).getOrigin();
    if (pos.x < ori.x){pos.x = ori.x+frame->getSize();}
    if (pos.x > ori.x+frame->getSize()){pos.x = ori.x;}
    if (pos.y < ori.y){pos.y = ori.y+frame->getSize();}
    if (pos.y > ori.y+frame->getSize()){pos.y = ori.y;}
    sprite.setPosition(pos);
    if (setPosHitbox){
        hitbox.setPosition(pos);
    }
    
}

sf::Vector2f Entity::getPos(){
    return pos;
}

float Entity::getAngle(){
    return angle;
}

void Entity::setAngle(float angle){
    this->angle = angle;
}