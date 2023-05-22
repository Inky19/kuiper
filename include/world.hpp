#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "utils.hpp"
#include "ship.hpp"
#include "asteroid.hpp"
#include "laser.hpp"
#include "debris.hpp"
#include "menu.hpp"

class World {
    public:
        World(sf::RenderWindow * window);
        void update(float dt, sf::Event * event);
        void pause(){pauseMenu.pause();};
    private:

        class Entities{
            public:
                std::vector<std::shared_ptr<Ship>> ships;
                std::vector<std::shared_ptr<Asteroid>> asteroids;
                std::vector<std::shared_ptr<Laser>> lasers;
                std::vector<std::shared_ptr<Debris>> debris;
                std::vector<std::vector<std::shared_ptr<Entity>>> getAllEntities();
        };
        
        bool debug;
        bool over;
        Entities entities;
        std::vector<std::unique_ptr<sf::Sound>> sounds;
        sf::RenderWindow * window;
        Frame frame = Frame(1000);
        PauseMenu pauseMenu = PauseMenu(window);
        
        void collisions();
        void render();
        void fire(std::shared_ptr<Ship> * ship);
        void generateAsteroids();
        void generateAsteroids(int number, int size);
        void generateAsteroids(int number, int size, sf::Vector2f pos);
        void updateEntities();
        void handleEvent(sf::Event * event);
        void clearSounds();
        void addSound(const sf::SoundBuffer * buffer);

};


#endif