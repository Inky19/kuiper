#include "laser.hpp"
#include "assetsLoader.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "utils.hpp"

Laser::Laser(float angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame){
    this->frame = frame;
    this->angle = angle;
    this->pos = pos;
    v0x = initialSpeed.x;
    v0y = initialSpeed.y;
    life = 0;
    expired = false;
    sprite.setOrigin(8,8);
    sprite.setTexture(Assets::laser);
    sprite.setRotation(angle);
    sprite.setPosition(pos);
    this->speed = 500;
}

void Laser::update(float dt){
    // Update position
    pos.x += (v0x+speed*sin(degToRad(angle)))*dt;
    pos.y += (v0y-speed*cos(degToRad(angle)))*dt;

    life += dt;
    if (life > maxLife){
        expired = true;
    }

    setInFrame();
}

void Laser::render(sf::RenderWindow * window){
    (*window).draw(sprite);
}