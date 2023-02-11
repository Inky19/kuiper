#ifndef DEBRIS_HPP
#define DEBRIS_HPP

#include <memory>
#include "entity.hpp"
#include "utils.hpp"


class Debris : public Entity{
    private:
        inline const static float maxLife = 5; // Duration of a debris in seconds
        float v0x;
        float v0y;
        float life;
        bool expired;
        float spriteAngle;
    public:
        Debris(float angle, sf::Vector2f pos, sf::Vector2f initialSpeed, Frame * frame);
        void update(float dt);
        void render(sf::RenderWindow * window, bool debug = false);
        bool isExpired(); 
};

#endif