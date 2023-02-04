#include "laser.hpp"
#include "assetsLoader.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "utils.hpp"
#include <memory>
#include "asteroid.hpp"
#include <iostream>

Laser::Laser(float angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame){
    this->frame = frame;
    this->angle = angle;
    this->pos = pos;
    tip.x = 8*sin(degToRad(angle));
    tip.y = -8*cos(degToRad(angle));
    v0x = initialSpeed.x;
    v0y = initialSpeed.y;
    life = 0;
    expired = false;
    sprite.setOrigin(8,8);
    sprite.setTexture(Assets::laser);
    sprite.setRotation(angle);
    sprite.setPosition(pos);
    this->speed = 500;

    hitbox = sf::CircleShape(6);
    hitbox.setFillColor(sf::Color(128,255,255,128));
    hitbox.setOutlineThickness(0);
    hitbox.setOrigin(6,6);
}

void Laser::update(float dt){
    // Update position
    pos.x += (v0x+speed*sin(degToRad(angle)))*dt;
    pos.y += (v0y-speed*cos(degToRad(angle)))*dt;

    life += dt;
    if (life > maxLife){
        expired = true;
    }

    setInFrame(false);
    hitbox.setPosition(pos+tip);
}

bool Laser::collide(std::shared_ptr<Asteroid> * asteroid){
    sf::Vector2f posAst = (*asteroid)->getPos();
    float distX = posAst.x - (pos+tip).x;
    float distY = posAst.y - (pos+tip).y;
    float distance = distX*distX + distY*distY;
    float maxDistance = (*asteroid)->getSize()/2;
    if (distance < maxDistance*maxDistance){
        hitbox.setFillColor(sf::Color(255,255,0,128));
        expired = true;
        return true;
    }
    return false;
}

void Laser::render(sf::RenderWindow * window, bool debug){
    (*window).draw(sprite);
    if (debug){
        (*window).draw(hitbox);
    }
    
}

bool Laser::isExpired(){
    return expired;
}