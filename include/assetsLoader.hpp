#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP

#include <SFML/Graphics.hpp>

class Assets{
    public:
        Assets();
        static const sf::Texture shipTexture;
        static const sf::Texture asteroid32;
        static const sf::Texture asteroid64;
        static const sf::Texture asteroid128;
        static const sf::Texture laser;
    private:
        static const sf::Texture loadTexture(std::string path);
};
#endif