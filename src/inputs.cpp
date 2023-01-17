#include <inputs.hpp>
#include <memory>
#include "ship.hpp"

void InputProcessor::keyPressed(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship){
    switch (key){
        case sf::Keyboard::Z:
            if(!pressingUp){
                (*ship)->setThrust(10000);
                pressingUp = true;
            }
            break;

        case sf::Keyboard::Q:
            if(!pressingLeft){
                (*ship)->setDAngle(-400);
                pressingLeft = true;
            }
            break;

        case sf::Keyboard::D:
            if(!pressingRight){
                (*ship)->setDAngle(400);
                pressingRight = true;
            }
            break;
            
        case sf::Keyboard::Space:
            if(!pressingFire){
                (*ship)->setFiring(true);
                pressingFire = true;
            }
            break;

        case sf::Keyboard::C:
            (*ship)->center();
            break;

        default:
            break;
    }
}

void InputProcessor::keyReleased(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship){
    switch (key){
    case sf::Keyboard::Q:
        if ((*ship)->getDAngle() < 0){
            (*ship)->setDAngle(0);
        }
        pressingLeft = false;
        break;

    case sf::Keyboard::D:
        if ((*ship)->getDAngle() > 0){
            (*ship)->setDAngle(0);
        }
        pressingRight = false;
        break;
    
    case sf::Keyboard::Z:
        (*ship)->setThrust(0);
        pressingUp = false;
        break;

    case sf::Keyboard::Space:
        pressingFire = false;
        break;
    
    default:
        break;
    }
}