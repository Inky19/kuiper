#include "world.hpp"
#include "inputs.hpp"
#include <iostream>
#include <memory>
#include <vector>

std::vector<std::vector<std::shared_ptr<Entity>>>  World::Entities::getAllEntities(){
    std::vector<std::vector<std::shared_ptr<Entity>>> ent;

    std::vector<std::shared_ptr<Entity>> shipsENT (ships.begin(), ships.end());
    std::vector<std::shared_ptr<Entity>> asteroidsENT (asteroids.begin(), asteroids.end());
    std::vector<std::shared_ptr<Entity>> lasersENT (lasers.begin(), lasers.end());
    ent.push_back(shipsENT);
    ent.push_back(asteroidsENT);
    ent.push_back(lasersENT);
    return ent;
}

World::World(sf::RenderWindow * window){
    this->window = window;    
    std::shared_ptr<Ship> ship = std::make_shared<Ship>(&frame);
    entities.ships.push_back(ship);
    debug = false;
    over = false;
    generateAsteroids();
}

void World::render(){
    (*window).clear();
        
    (*window).draw(frame.getBorder());
    
    
    for (std::vector<std::shared_ptr<Entity>> arr : entities.getAllEntities()){
        for (std::shared_ptr<Entity> e : arr){
            e->render(window, debug);
        }
    }
    (*window).display();
}

void World::fire(std::shared_ptr<Ship> * ship){
    std::shared_ptr<Laser> laser = std::make_shared<Laser>((*ship)->getAngle(), (*ship)->getPos(), (*ship)->getSpeedVector(), &frame);
    (*ship)->setFiring(false);
    entities.lasers.push_back(laser);
}

void World::update(float dt, sf::Event * event){
    while ((*window).pollEvent(*event)){
        switch (event->type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event->key.code == sf::Keyboard::F3){
                    debug = !debug;
                } else {
                    InputProcessor::keyPressed(event->key.code, &entities.ships);
                }
                break;
            case sf::Event::KeyReleased:
                InputProcessor::keyReleased(event->key.code, &entities.ships);
                break;
            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, event->size.width, event->size.height);
                float size = std::min(event->size.width, event->size.height);
                frame.setSize(size);
                (*window).setView(sf::View(visibleArea));
                frame.setOrigin((event->size.width-size)/2,(event->size.height-size)/2);
                break;
            }
    }

    for (std::vector<std::shared_ptr<Entity>> arr : entities.getAllEntities()){
        for (std::shared_ptr<Entity> e : arr){
            (*e).update(dt);
        }
    }
    
    for (std::shared_ptr<Ship> ship : entities.ships){
        if(ship->isFiring()){
            fire(&ship);
        }
    }
    updateEntities();
    render();
}

void World::updateEntities(){
    std::erase_if(entities.lasers, [](const std::shared_ptr<Laser>& laser){return laser->isExpired();});
    entities.lasers.shrink_to_fit();
    std::erase_if(entities.ships, [](const std::shared_ptr<Ship>& ship){return ship->isCollided();});
    entities.ships.shrink_to_fit();
    collisions();
}

void World::collisions(){
    
    for (int i=0 ; i<entities.asteroids.size() ; i++){
        for (int j=i+1 ; j<entities.asteroids.size() ; j++){
            Asteroid::collide(&(entities.asteroids)[i], &(entities.asteroids)[j]);
        }
        for (std::shared_ptr<Ship> ship : entities.ships){
            ship->collide(&(entities.asteroids)[i]);
            
        }
    }
    bool collided = false;
    int index = 0;
    for (std::shared_ptr<Laser> laser : entities.lasers){
        for (int i=0; i<entities.asteroids.size(); i++){
            if(collided = laser->collide(&entities.asteroids[i])){
                index = i;
                break;
            };
        }
        if (collided){
            entities.asteroids[index]->eraseCollisions(&entities.asteroids[index]);
            entities.asteroids.erase(entities.asteroids.begin() + index);
            entities.asteroids.shrink_to_fit();
            collided = false;
        }
    }
    
}



void World::generateAsteroids(){
    for (int i=0; i<10; i++){
        std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(64, &frame);
        entities.asteroids.push_back(asteroid);
    }
}