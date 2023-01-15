#include "asteroid.hpp"
#include "utils.hpp"
#include "entity.hpp"
#include <memory>
#include <math.h>

#include <iostream>

/**
 * @param m Mass of the asteroid. Used to determine its size.
 * @param frame Pointer of the frame where the asteroid will be placed.
*/
Asteroid::Asteroid(int m, Frame *frame){
    this->frame = frame;
    mass = m;
    size = 32;

    // The size of the asteroid can have 3 values, depending of its mass.
    // These values need to be the same as the one in the texture files.
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
    pos = getBorder(angle, frame); // The asteroid is placed at the border of the frame at the start of the game.

    if (sprite.getTexture() == nullptr){ // Load texture
        sf::Texture *texture = new sf::Texture;
        //TODO: texture statique ?
        // The texture file 
        (*texture).loadFromFile("assets/textures/aste" + std::to_string(size) + ".png");
        sprite.setTexture(*texture);
        sprite.setRotation(spriteAngle);
    }
}

/**
 * Calculates and updates the caracteristics of the asteroid.
 * 
 * @param dt Time in seconds since the last call
*/
void Asteroid::update(float dt){
    // Update position
    pos.x += speed*sin(degToRad(angle))*dt;
    pos.y += -speed*cos(degToRad(angle))*dt;
    
    // Update sprite rotation
    spriteAngle = fmod(spriteAngle + dt*20, 360);
    sprite.setRotation(spriteAngle);

    setInFrame(); // Place the asteroid inside the frame's borders.

    // Debug colors for collisions
    if (ongoingCollisions.size() > 0){
        hitbox.setFillColor(sf::Color(0,255,0,128));
    } else {
        hitbox.setFillColor(sf::Color(255,0,0,128));
    }
}

void Asteroid::render(sf::RenderWindow * window){
    window->draw(hitbox);
    window->draw(sprite);
}

/**
 * Static member function to check if two asteroids are colliding.
 * Updates ongoingCollisions accordingly.
 * 
 * @param asteroid1 Shared pointer of the first asteroid
 * @param asteroid2 Shared pointer of the second asteroid
*/
void Asteroid::collide(std::shared_ptr<Asteroid> * asteroid1, std::shared_ptr<Asteroid> * asteroid2){
    sf::Vector2f pos1 = (*asteroid1)->getPos();
    sf::Vector2f pos2 = (*asteroid2)->getPos();
    float distX = pos1.x - pos2.x;
    float distY = pos1.y-pos2.y;
    float distance = distX*distX + distY*distY;
    int maxDistance = ((*asteroid1)->getSize()+(*asteroid2)->getSize())/2;
    bool colliding = distance < maxDistance*maxDistance;
    
    if (colliding){
        int alreadyColliding = (*asteroid1)->checkCollision(asteroid2);
        if (alreadyColliding == -1){
            (*asteroid1)-> addCollision(asteroid2);
            (*asteroid2)-> addCollision(asteroid1);

            //TODO: Direction is simply swaped. COULD BE REDONE WITH BETTER PHYSICS ACCOUNTING FOR ANGLE OF IMPACT
            float tempAngle = (*asteroid1)->getAngle();
            (*asteroid1)->setAngle((*asteroid2)->getAngle());
            (*asteroid2)->setAngle(tempAngle);
        }
    } else {
        (*asteroid1)-> removeCollision(asteroid2);
        (*asteroid2)-> removeCollision(asteroid1);
        
    }    
}

// 
void Asteroid::addCollision(std::shared_ptr<Asteroid> * asteroid){
    std::weak_ptr<Asteroid> * smartWeak = new std::weak_ptr<Asteroid>(*asteroid);
    ongoingCollisions.push_back((*smartWeak));
}

/** Removes an asteroid from ongoingCollisions (if present)
 * 
 * @param asteroid Shared pointer of the asteroid to remove
 */
void Asteroid::removeCollision(std::shared_ptr<Asteroid> * asteroid){
    int index = checkCollision(asteroid);
    if (index >= 0){
        ongoingCollisions.erase(ongoingCollisions.begin() + index);
        ongoingCollisions.shrink_to_fit();
    }
}

/** 
 * Checks if an asteroid is already in the vector ongoingCollisions.
 * Returns its index if true, else returns -1.
 * 
 * @param asteroid Shared pointer of the asteroid to check
 */
int Asteroid::checkCollision(std::shared_ptr<Asteroid> * asteroid){
    int index = -1;
    for (int i = 0; i<ongoingCollisions.size(); i++){
        if ((ongoingCollisions[i].lock()) == *asteroid){
            index = i;
        }
    }
    return index;
}

int Asteroid::getSize(){
    return size;
}