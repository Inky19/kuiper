#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "entity.hpp"

class Asteroid : private Entity{
    public:
        Asteroid(int m, Frame *frame);
        void update();

};

#endif