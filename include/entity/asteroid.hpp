#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"
#include <memory>

class Asteroid : public Entity{
    private:
        float spriteAngle; // Angle of the sprite used to make the asteroid rotate
        
        std::vector<std::weak_ptr<Asteroid>> ongoingCollisions; // Current collisions (a collision can last multiple frames)
    public:
        Asteroid(int m, Frame *frame);
        void update(float dt);
        void render(sf::RenderWindow * window, bool debug);
        static void collide(std::shared_ptr<Asteroid> * asteroid1, std::shared_ptr<Asteroid> * asteroid2);
        int getSize();
        void addCollision(std::shared_ptr<Asteroid> * asteroid);
        void removeCollision(std::shared_ptr<Asteroid> * asteroid);
        void eraseCollisions(std::shared_ptr<Asteroid> * asteroid);
        int checkCollision(std::shared_ptr<Asteroid> * asteroid);
};

#endif