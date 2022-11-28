//#include <inputs.hpp>
#include "ship.hpp"

void keyPressed(sf::Keyboard::Key key, Ship *ship){
    switch (key){
        case sf::Keyboard::Z :
            (*ship).setThrust(10000);
            break;
        case sf::Keyboard::Q:
            (*ship).setDAngle(400);
            break;

        case sf::Keyboard::D:
            (*ship).setDAngle(-400);
            break;
        default:
            break;
    }
}

void keyReleased(sf::Keyboard::Key key, Ship *ship){
    switch (key){
    case sf::Keyboard::Q:
        if ((*ship).getDAngle() > 0){
            (*ship).setDAngle(0);
        }
        break;

    case sf::Keyboard::D:
        if ((*ship).getDAngle() < 0){
            (*ship).setDAngle(0);
        }
        break;
    
    case sf::Keyboard::Z:
        (*ship).setThrust(0);
        break;
    
    default:
        break;
    }
}