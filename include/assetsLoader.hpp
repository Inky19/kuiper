#ifndef ASSETSLOADER_HPP
#define ASSETSLOADER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Assets{
    public:
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

        static const sf::SoundBuffer laserFX;
        static const sf::SoundBuffer deathFX;
        static const sf::SoundBuffer splitFX;

        static const sf::Font millimetre;
    private:
        static const sf::Texture loadTexture(std::string path);
        static const sf::Font loadFont(std::string path);
        static const sf::SoundBuffer loadSound(std::string path);
};
#endif