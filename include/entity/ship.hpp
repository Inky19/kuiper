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

        float getSpeed();
        float getDAngle();
        void setDAngle(float angle);
        float getThrust();
        void setThrust(float thrust);
        void toBorder();
        void center();
    private:
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