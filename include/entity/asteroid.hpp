#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"
#include <memory>

class Asteroid : public Entity{
    private:
        float spriteAngle;
        int size;
        std::vector<std::weak_ptr<Asteroid>> ongoingCollisions;
        std::vector<std::weak_ptr<Asteroid>> newCollisions;
        bool externalCollision;
    public:
        Asteroid(int m, Frame *frame);
        void update(float dt);
        void render(sf::RenderWindow * window);
        void collide(std::shared_ptr<Asteroid> * asteroid);
        int getSize();
        void setExternalColliding(bool colliding);

};

#endif