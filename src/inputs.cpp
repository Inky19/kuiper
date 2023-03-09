#include <inputs.hpp>
#include <memory>
#include <iostream>
#include "ship.hpp"

void InputProcessor::keyPressed(sf::Keyboard::Key key, std::vector<std::shared_ptr<Ship>> *ships){
    bool shipActive = (((*ships).size() > 0)) && !(*ships)[0]->isCollided();
    if (shipActive){   
        switch (key){
            case sf::Keyboard::Z:
                if(!pressingUp){
                    (*ships)[0]->setThrust(10000);
                    pressingUp = true;
                }
                break;

            case sf::Keyboard::Q:
                if(!pressingLeft){
                    (*ships)[0]->setDAngle(-400);
                    pressingLeft = true;
                }
                break;

            case sf::Keyboard::D:
                if(!pressingRight){
                    (*ships)[0]->setDAngle(400);
                    pressingRight = true;
                }
                break;
                
            case sf::Keyboard::Space:
                if(!pressingFire){
                    (*ships)[0]->setFiring(true);
                    pressingFire = true;
                }
                break;

            case sf::Keyboard::C:
                (*ships)[0]->center();
                break;

            default:
                break;
        }
    }
}

void InputProcessor::keyReleased(sf::Keyboard::Key key, std::vector<std::shared_ptr<Ship>> *ships){
    bool shipActive = (((*ships).size() > 0)) && !(*ships)[0]->isCollided();
    if (shipActive){   
        switch (key){
        case sf::Keyboard::Q:
            if ((*ships)[0]->getDAngle() < 0){
                (*ships)[0]->setDAngle(0);
            }
            pressingLeft = false;
            break;

        case sf::Keyboard::D:
            if ((*ships)[0]->getDAngle() > 0){
                (*ships)[0]->setDAngle(0);
            }
            pressingRight = false;
            break;
        
        case sf::Keyboard::Z:
            (*ships)[0]->setThrust(0);
            pressingUp = false;
            break;

        case sf::Keyboard::Space:
            pressingFire = false;
            break;
        
        default:
            break;
        }
    }
}