#include "ship.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include "assetsLoader.hpp"
#include "laser.hpp"
#include <math.h>
#include <iostream>

Ship::Ship(Frame *frame){
    this->frame = frame;
    firing = false;
    collided = false;
    mass = 10;
    angle = 0;
    speed = 10;
    propx = 0;
    propy = 0;
    dAngle = 0;
    thrust = 0;
    animationTimer = 0;
    vx = 0;
    vy = 0;
    if (sprite.getTexture() == nullptr){
        
        sprite.setTexture(Assets::shipTexture);
        size = (sprite.getTexture()->getSize()).x;
        sprite.setOrigin(size/2,size/2);
        sprite.setRotation(angle);
    }
    pos = sf::Vector2f(frame->getOrigin().x+frame->getSize()/2,frame->getOrigin().y+frame->getSize()/2);
    sprite.setPosition(pos);
    hitbox = sf::CircleShape(6);
    hitbox.setOrigin(6,6);
    hitbox.setFillColor(sf::Color(255,0,255,128));
    hitbox.setOutlineThickness(0);

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
    updateSprite(dt);
    hitbox.setFillColor(sf::Color(255,0,255,128));
    int hitboxRadius = (size-2)/2;
    hitboxPoints[0] = sf::Vector2f(sin(degToRad(angle))*hitboxRadius,-cos(degToRad(angle))*hitboxRadius);
    hitboxPoints[1] = sf::Vector2f(sin(degToRad(angle+130))*hitboxRadius,-cos(degToRad(angle+130))*hitboxRadius);
    hitboxPoints[2] = sf::Vector2f(sin(degToRad(angle+240))*hitboxRadius,-cos(degToRad(angle+240))*hitboxRadius);
}

void Ship::updateSprite(float dt){
    if (thrust>0){
        animationTimer += dt;
        if (animationTimer < 0.04){
            sprite.setTexture(Assets::shipThurster0);
        } else if (animationTimer < 0.08){
            sprite.setTexture(Assets::shipThurster1);
        } else if (animationTimer < 0.12){
            sprite.setTexture(Assets::shipThurster2);
        } else if (animationTimer < 0.16) {
            sprite.setTexture(Assets::shipThurster3);
        } else {
            animationTimer = 0;
        }
        
    } else {
        sprite.setTexture(Assets::shipTexture);
    }
}

void Ship::setFiring(bool firing){
    this->firing = firing;
}

bool Ship::isFiring(){
    return firing;
}

sf::Vector2f Ship::getSpeedVector(){
    return sf::Vector2f(vx,vy);
}

void Ship::render(sf::RenderWindow * window, bool debug){
    window->draw(sprite);
    if (debug){
        window->draw(hitbox);
        for (int i=0; i<3.; i++){
        sf::CircleShape circle = sf::CircleShape(4);
        circle.setPosition(pos+hitboxPoints[i]);
        circle.setOrigin(4,4);
        circle.setFillColor(sf::Color(255,255,0,128));
        window->draw((circle));
    }
    
    }
}

bool Ship::collide(std::shared_ptr<Asteroid> * asteroid){
    for (int i=0; i<3.; i++){
        sf::Vector2f posAstr = (*asteroid)->getPos();
        float distX = posAstr.x - (pos.x +hitboxPoints[i].x);
        float distY = posAstr.y - (pos.y +hitboxPoints[i].y);
        float distance = distX*distX + distY*distY;
        int maxDistance = (*asteroid)->getSize()/2;
        bool colliding = distance < maxDistance*maxDistance;
        if (colliding){
            hitbox.setFillColor(sf::Color(255,255,255,128));
            collided = true;
            return true;
        }
    } 
    return false;
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

bool Ship::isCollided(){
    return collided;
}