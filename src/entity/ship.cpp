#include "ship.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include <math.h>
#include <iostream>

Ship::Ship(Frame *frame){
    this->frame = frame;
    mass = 10;
    angle = 0;
    speed = 10;
    propx = 0;
    propy = 0;
    dAngle = 0;
    thrust = 0;
    vx = 0;
    vy = 0;
    if (sprite.getTexture() == nullptr){
        sf::Texture *texture = new sf::Texture;
        (*texture).loadFromFile("assets/textures/ship.png");
        sprite.setOrigin(16,16);
        sprite.setTexture(*texture);
        sprite.setRotation(angle);
    }
    pos = sf::Vector2f(frame->getOrigin().x+frame->getSize()/2,frame->getOrigin().y+frame->getSize()/2);
    sprite.setPosition(pos);
}

void Ship::update(float dt){
    if (dAngle != 0){
        angle += dAngle*dt;
        if (angle > 0){
            angle = fmod(angle, 360);
        }else{
            angle = 360 - fmod(-angle, 360);
        }
        
        sprite.setRotation(angle);
    }
    float v0X = (thrust/drag)*sin(degToRad(angle));
    float v0Y = -(thrust/drag)*cos(degToRad(angle));
    
    vx = (vx-v0X)*exp(-(drag/mass)*dt)+v0X;
    vy = (vy-v0Y)*exp(-(drag/mass)*dt)+v0Y;
    pos.x += vx*dt;
    pos.y += vy*dt;
    setInFrame();
}

void Ship::render(sf::RenderWindow * window){
    window->draw(sprite);
}


void Ship::move(){
        
}

void Ship::toBorder(){
    sf::Vector2f newPos = getBorder(angle,frame);
    pos.x = newPos.x;
    pos.y = newPos.y;
    sprite.setPosition(pos);
}

void Ship::center(){
    pos = sf::Vector2f(500,500);
    sprite.setPosition(pos);
}

void Ship::rotate(float a){
    if (a > 0){
        angle = fmod(angle+a, 360);
    } else if (a < 0){
        angle = fmod(angle-a, 360);
    }
    std::cout << angle << std::endl;
    sprite.setRotation(angle);
}


float Ship::getSpeed(){
    return speed;
}

float Ship::getDAngle(){
    return dAngle;
}

void Ship::setDAngle(float agl){
    dAngle = agl;
}

float Ship::getThrust(){
    return thrust;
}

void Ship::setThrust(float thr){
    thrust = thr;
}