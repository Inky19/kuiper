#include "asteroid.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include <math.h>

Asteroid::Asteroid(int m, Frame *frame){
    this->frame = frame;
    externalCollision = false;
    mass = m;
    size = 32;
    if (m <= 32){
        size = 32;
    } else if (m <= 64){
        size = 64;
    } else {
        size = 128;
    }
    hitbox = sf::CircleShape(size/2);
    hitbox.setFillColor(sf::Color(255,0,0,128));
    hitbox.setOutlineThickness(0);
    sprite.setOrigin(size/2,size/2);
    hitbox.setOrigin(size/2,size/2);
    angle = randInt(0,359);
    spriteAngle = randInt(0,359);
    speed = 100;
    pos = getBorder(angle, frame);
    if (sprite.getTexture() == nullptr){
        sf::Texture *texture = new sf::Texture;
        (*texture).loadFromFile("assets/textures/aste" + std::to_string(size) + ".png");
        sprite.setTexture(*texture);
        sprite.setRotation(spriteAngle);
    }
}

void Asteroid::update(float dt){
    pos.x += speed*sin(angle)*dt;
    pos.y += -speed*cos(angle)*dt;
    spriteAngle = fmod(spriteAngle + dt*20, 360);
    sprite.setRotation(spriteAngle);
    setInFrame();
    if (ongoingCollisions.size() > 0 || externalCollision){
        hitbox.setFillColor(sf::Color(0,255,0,128));
    } else {
        hitbox.setFillColor(sf::Color(255,0,0,128));
    }
    Asteroid * ast;
    for (int i=0; i<newCollisions.size(); i++){
        ongoingCollisions.push_back(newCollisions[i]);
    }
    newCollisions.clear();
    externalCollision = false;
}

void Asteroid::render(sf::RenderWindow * window){
    window->draw(hitbox);
    window->draw(sprite);
}

void Asteroid::collide(Asteroid * asteroid){
    sf::Vector2f pos2 = asteroid->getPos();
    float distX = pos.x - pos2.x;
    float distY = pos.y-pos2.y;
    float distance = distX*distX + distY*distY;
    int maxDistance = (size+asteroid->getSize())/2;
    bool colliding = false;
    int index = -1;
    for (int i = 0; i<ongoingCollisions.size(); i++){
        if (ongoingCollisions[i] == asteroid){
            colliding = true;
            asteroid->setExternalColliding(true);
            index = i;
            break;
        }
    }
    bool intersect = distance < maxDistance*maxDistance;
    if (intersect && !colliding){
        newCollisions.push_back(asteroid);
    } else if (!intersect && colliding){
        ongoingCollisions.erase(ongoingCollisions.begin() + index);
    }
}

void Asteroid::setExternalColliding(bool colliding){
    externalCollision = colliding;
}

int Asteroid::getSize(){
    return size;
}