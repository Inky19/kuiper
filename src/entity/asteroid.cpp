#include "asteroid.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include <math.h>

Asteroid::Asteroid(int m, Frame *frame){
    this->frame = frame;
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
    spriteAngle += dt*20;
    sprite.setRotation(spriteAngle);
    setInFrame();
}

void Asteroid::render(sf::RenderWindow * window){
    window->draw(hitbox);
    window->draw(sprite);
}