#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"

class Asteroid : public Entity{
    private:
        float spriteAngle;
        int size;
        std::vector<Asteroid *> ongoingCollisions;
        std::vector<Asteroid *> newCollisions;
        bool externalCollision;
    public:
        Asteroid(int m, Frame *frame);
        void update(float dt);
        void render(sf::RenderWindow * window);
        void collide(Asteroid * asteroid);
        int getSize();
        void setExternalColliding(bool colliding);

};

#endif