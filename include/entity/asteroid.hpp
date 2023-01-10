#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"

class Asteroid : public Entity{
    private:
        float spriteAngle;
        int size;
    public:
        Asteroid(int m, Frame *frame);
        void update(float dt);
        void render(sf::RenderWindow * window);

};

#endif