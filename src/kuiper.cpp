#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "utils.hpp"
#include "ship.hpp"
#include "inputs.hpp"
#include "entity.hpp"
#include "laser.hpp"
#include "asteroid.hpp"
#include "world.hpp"
#include "menu.hpp"

int main(){
    sf::Clock timer;
    float dt = 0;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Kuiper");
    World world(&window);
    Frame frame(1000);
    MainMenu mainMenu(&window, &frame);
    while (window.isOpen() && !mainMenu.isStarting()){
        sf::Event event;
        mainMenu.update(&event);
        //
    }
    while (window.isOpen()){
        sf::Event event;
        dt = timer.restart().asSeconds();
        world.update(dt, &event);
    }
    return 0;
}

