#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <SFML/Graphics.hpp>

void keyPressed(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship);
void keyReleased(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship);

#endif