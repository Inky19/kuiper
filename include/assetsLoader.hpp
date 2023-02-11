#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP

#include <SFML/Graphics.hpp>

class Assets{
    public:
        Assets();
        static const sf::Texture shipTexture;
        static const sf::Texture shipThurster0;
        static const sf::Texture shipThurster1;
        static const sf::Texture shipThurster2;
        static const sf::Texture shipThurster3;
        static const sf::Texture asteroid32;
        static const sf::Texture asteroid64;
        static const sf::Texture asteroid128;
        static const sf::Texture laser;
        static const sf::Texture debris;
    private:
        static const sf::Texture loadTexture(std::string path);
};
#endif