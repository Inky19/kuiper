#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"

class Ship : public Entity{
    public:
        Ship(Frame * frame);
        void move();
        void rotate(float a);

        void update(float dt);
        void render(sf::RenderWindow * window);
        void collide(Entity * entity);

        sf::Vector2f getSpeedVector();
        float getSpeed();
        float getDAngle();
        void setDAngle(float angle);
        float getThrust();
        void setThrust(float thrust);
        void toBorder();
        void center();
        bool isFiring();
        void setFiring(bool firing);
    private:
        bool firing;
        float vx;
        float vy;
        int thrust;
        float propx;
        float propy;
        static const int maxSpeed = 10;
        static const int drag = 20;
        void updateSprite();
        
        float dAngle;
};

#endif