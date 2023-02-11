#include "assetsLoader.hpp"
#include <SFML/Graphics.hpp>

const sf::Texture Assets::loadTexture(std::string path){
    sf::Texture * texture = new sf::Texture();
    (*texture).loadFromFile(path);
    return (*texture);
}

const sf::Texture Assets::shipTexture = Assets::loadTexture("assets/textures/ship.png");
const sf::Texture Assets::shipThurster0 = Assets::loadTexture("assets/textures/ship_thruster_0.png");
const sf::Texture Assets::shipThurster1 = Assets::loadTexture("assets/textures/ship_thruster_1.png");
const sf::Texture Assets::shipThurster2 = Assets::loadTexture("assets/textures/ship_thruster_2.png");
const sf::Texture Assets::shipThurster3 = Assets::loadTexture("assets/textures/ship_thruster_3.png");
const sf::Texture Assets::asteroid32 = Assets::loadTexture("assets/textures/asteroid32.png");
const sf::Texture Assets::asteroid64 = Assets::loadTexture("assets/textures/asteroid64.png");
const sf::Texture Assets::asteroid128 = Assets::loadTexture("assets/textures/asteroid128.png");
const sf::Texture Assets::laser = Assets::loadTexture("assets/textures/laser.png");
const sf::Texture Assets::debris = Assets::loadTexture("assets/textures/debris.png");