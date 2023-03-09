#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include "ship.hpp"
#include "world.hpp"

class InputProcessor{
    private:
        inline static bool pressingFire = false;
        inline static bool pressingUp = false;
        inline static bool pressingLeft = false;
        inline static bool pressingRight = false;
    public:
        static void keyPressed(sf::Keyboard::Key key, std::vector<std::shared_ptr<Ship>> *ships);
        static void keyReleased(sf::Keyboard::Key key, std::vector<std::shared_ptr<Ship>> *ships);
};

#endif