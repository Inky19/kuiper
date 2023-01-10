#include "asteroid.hpp"
#include "utils.hpp"
#include "entity.hpp"

Asteroid::Asteroid(int m, Frame *frame){
    this->frame = frame;
    mass = m;
    sprite.setOrigin(mass/2,mass/2);
    pos = sf::Vector2f(0,0);
    angle = randInt(0,359);
    pos = getBorder(angle, frame);
    if (sprite.getTexture() == nullptr){
        sf::Texture *texture = new sf::Texture;
        (*texture).loadFromFile("assets/textures/ast64.png");
        sprite.setOrigin(32,32);
        sprite.setTexture(*texture);
    }
}
