#ifndef LASER_HPP
#define LASER_HPP

#include <memory>
#include "entity.hpp"
#include "utils.hpp"
#include "asteroid.hpp"


class Laser : public Entity{
    private:
        inline const static float maxLife = 1; // Duration of a laser in seconds
        sf::Vector2f tip;
        float v0x;
        float v0y;
        float life;
        bool expired;
    public:
        Laser(float angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame);
        void update(float dt);
        void render(sf::RenderWindow * window, bool debug = false);
        bool isExpired();
        bool collide(std::shared_ptr<Asteroid> * asteroid);
        
};

#endif