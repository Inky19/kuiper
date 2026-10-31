#include <inputs.hpp>
#include <memory>
#include <iostream>
#include "ship.hpp"

void InputProcessor::keyPressed(sf::Keyboard::Scancode key, std::vector<std::shared_ptr<Ship>> *ships){
    bool shipActive = (((*ships).size() > 0)) && !(*ships)[0]->isCollided();
    if (shipActive){   
        switch (key){
            case sf::Keyboard::Scancode::W:
                if(!pressingUp){
                    (*ships)[0]->setThrust(10000);
                    pressingUp = true;
                }
                break;

            case sf::Keyboard::Scancode::A:
                if(!pressingLeft){
                    (*ships)[0]->setDAngle(-400);
                    pressingLeft = true;
                }
                break;

            case sf::Keyboard::Scancode::D:
                if(!pressingRight){
                    (*ships)[0]->setDAngle(400);
                    pressingRight = true;
                }
                break;
                
            case sf::Keyboard::Scancode::Space:
                if(!pressingFire){
                    (*ships)[0]->setFiring(true);
                    pressingFire = true;
                }
                break;

            case sf::Keyboard::Scancode::C:
                (*ships)[0]->center();
                break;

            default:
                break;
        }
    }
}

void InputProcessor::keyReleased(sf::Keyboard::Scancode key, std::vector<std::shared_ptr<Ship>> *ships){
    bool shipActive = (((*ships).size() > 0)) && !(*ships)[0]->isCollided();
    if (shipActive){   
        switch (key){
        case sf::Keyboard::Scancode::A:
            if ((*ships)[0]->getDAngle() < 0){
                (*ships)[0]->setDAngle(0);
            }
            pressingLeft = false;
            break;

        case sf::Keyboard::Scancode::D:
            if ((*ships)[0]->getDAngle() > 0){
                (*ships)[0]->setDAngle(0);
            }
            pressingRight = false;
            break;
        
        case sf::Keyboard::Scancode::W:
            (*ships)[0]->setThrust(0);
            pressingUp = false;
            break;

        case sf::Keyboard::Scancode::Space:
            pressingFire = false;
            break;
        
        default:
            break;
        }
    }
}