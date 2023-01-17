#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "ship.hpp"

class InputProcessor{
    private:
        inline static bool pressingFire = false;
        inline static bool pressingUp = false;
        inline static bool pressingLeft = false;
        inline static bool pressingRight = false;
    public:
        static void keyPressed(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship);
        static void keyReleased(sf::Keyboard::Key key, std::shared_ptr<Ship> *ship);
};

#endif