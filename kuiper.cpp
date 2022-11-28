#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "ship.hpp"
#include "inputs.hpp"

int main(){
    sf::Clock timer;
    float dt = 0;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Kuiper");
    Ship ship;
    while (window.isOpen()){
        sf::Event event;
        dt = timer.restart().asSeconds();
        while (window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    keyPressed(event.key.code, &ship);
                    break;
                case sf::Event::KeyReleased:
                    keyReleased(event.key.code, &ship);
                    break;
            }
        
        }
        ship.update(dt);
        window.clear();
        window.draw(ship.getSprite());
        window.display();
    }
return 0;
}