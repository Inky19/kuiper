#include "debris.hpp"
#include "assetsLoader.hpp"
#include <math.h>

Debris::Debris(float angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame){
    this->frame = frame;
    this->angle = angle;
    this->pos = pos;
    v0x = initialSpeed.x;
    v0y = initialSpeed.y;
    expired = false;
    life = 0;
    sprite.setOrigin(8,8);
    sprite.setTexture(Assets::debris);
    sprite.setRotation(angle);
    sprite.setPosition(pos);
    this->speed = 200;
    spriteAngle = randInt(0,360);
}

void Debris::render(sf::RenderWindow * window, bool debug){
    (*window).draw(sprite);
}

void Debris::update(float dt){
    pos.x += (v0x+speed*sin(degToRad(angle)))*dt;
    pos.y += (v0y-speed*cos(degToRad(angle)))*dt;

    life += dt;
    if (life > maxLife){
        expired = true;
    }

    setInFrame(false);

    spriteAngle = fmod(spriteAngle + dt*400, 360);
    sprite.setRotation(spriteAngle);
}

bool Debris::isExpired(){
    return expired;
}