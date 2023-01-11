#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "ship.hpp"
#include "inputs.hpp"
#include "entity.hpp"
#include "asteroid.hpp"

void render(sf::RenderWindow * window, std::vector<Entity *> * entities){
    for (Entity* e : (* entities)){
        (*e).render(window);
    }
}

void update(std::vector<Entity *> * entities, float dt){
    for (Entity* e : (* entities)){
        (*e).update(dt);
    }
}

void collisions(std::vector<Asteroid *> * asteroids, Ship * ship){
    for (int i=0 ; i<asteroids->size() ; i++){
        for (int j=i+1 ; j<asteroids->size() ; j++){

            (*asteroids)[i]->collide((*asteroids)[j]);
            
        }
    }
}

std::vector<Asteroid *> generateAsteroids(std::vector<Entity *> * entities, Frame * frame){
    std::vector<Asteroid *> asteroids;
    for (int i=0; i<10; i++){
        Asteroid * asteroid = new Asteroid(64, frame);
        entities->push_back(asteroid);
        asteroids.push_back(asteroid);
    }
    return asteroids;
}

int main(){
    sf::Clock timer;
    float dt = 0;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Kuiper");
    Frame frame(1000);
    Ship ship(&frame);
    std::vector<Entity *> entities;
    entities.push_back(&ship);
    std::vector<Asteroid *> asteroids = generateAsteroids(&entities, &frame);
    while (window.isOpen()){
        sf::Event event;
        dt = timer.restart().asSeconds();
        while (window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::T){
                        ship.toBorder();
                    }
                    keyPressed(event.key.code, &ship);
                    break;
                case sf::Event::KeyReleased:
                    keyReleased(event.key.code, &ship);
                    break;
                case sf::Event::Resized:
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    float size = std::min(event.size.width, event.size.height);
                    frame.setSize(size);
                    window.setView(sf::View(visibleArea));
                    frame.setOrigin((event.size.width-size)/2,(event.size.height-size)/2);
                    break;
            }
        
        }
        window.clear();
        
        window.draw(frame.getBorder());
        update(&entities, dt);
        collisions(&asteroids, &ship);
        render(&window, &entities);
        
        window.display();
    }
return 0;
}

