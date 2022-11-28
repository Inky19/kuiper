#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>

class Ship : public sf::Transformable{
    public:
        Ship();
        sf::Sprite getSprite();
        void move();
        void rotate(float a);

        void update(float dt);

        float getSpeed();
        float getDAngle();
        void setDAngle(float angle);
        float getThrust();
        void setThrust(float thrust);
    private:
        float speed;
        float vx;
        float vy;
        int thrust;
        float propx;
        float propy;
        static const int maxSpeed = 10;
        static const int drag = 20;
        float mass;
        sf::Vector2f pos;
        float angle;
        sf::Sprite sprite;
        void updateSprite();
        
        float dAngle;
};

#endif