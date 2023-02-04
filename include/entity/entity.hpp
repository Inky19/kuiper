#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "utils.hpp"

class Entity : public sf::Transformable{
    protected:
        float mass;
        sf::Vector2f pos;
        float speed;
        float angle;
        sf::Sprite sprite;
        Frame *frame;
        sf::CircleShape hitbox;
        int size; // Size of the sprite
        
        void setInFrame(bool setPosHitbox = true);

    public:
        virtual ~Entity() = 0;
        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow * window, bool debug = false) = 0;
        sf::Vector2f getPos();
        sf::Sprite getSprite();
        float getAngle();
        void setAngle(float angle);
};

#endif