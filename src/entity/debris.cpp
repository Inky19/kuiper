#include "debris.hpp"
#include "assetsLoader.hpp"
#include <math.h>

Debris::Debris(sf::Angle angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame) : Entity::Entity(Assets::debris){
    this->frame = frame;
    this->angle = angle;
    this->pos = pos;
    v0x = initialSpeed.x;
    v0y = initialSpeed.y;
    expired = false;
    life = 0;
    sprite.setOrigin({8, 8});
    sprite.setRotation(angle);
    sprite.setPosition(pos);
    this->speed = 200;
    spriteAngle = sf::degrees(randInt(0,360));
}

void Debris::render(sf::RenderWindow * window, bool debug){
    (*window).draw(sprite);
}

void Debris::update(float dt){
    pos.x += (v0x+speed*sin(angle.asRadians()))*dt;
    pos.y += (v0y-speed*cos(angle.asRadians()))*dt;

    life += dt;
    if (life > maxLife){
        expired = true;
    }

    setInFrame(false);

    spriteAngle = sf::degrees(fmod(spriteAngle.asDegrees() + dt*400, 360));
    sprite.setRotation(spriteAngle);
}

bool Debris::isExpired(){
    return expired;
}