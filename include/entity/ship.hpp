#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"
#include <memory>
#include "asteroid.hpp"

class Ship : public Entity{
    public:
        Ship(Frame * frame);
        void move();
        void rotate(float a);
        void render(sf::RenderWindow * window, bool debug = false);
        void update(float dt);
        bool collide(std::shared_ptr<Asteroid> * asteroid);

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
        bool isCollided();
    private:
        bool firing;
        float vx;
        float vy;
        int thrust;
        float propx;
        float propy;
        bool collided;
        float animationTimer;

        sf::Vector2f hitboxPoints[3];

        static const int maxSpeed = 10;
        static const int drag = 20;
        void updateSprite(float dt);
        
        float dAngle;
};

#endif