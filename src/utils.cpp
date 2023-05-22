#include <math.h>
#include <random>
#include "utils.hpp"
#include "menu.hpp"
#include <iostream>

/**
 * Converts a value in degrees to radians.
 * 
 * @param angle Angle in degrees
 * @return Angle in radians
*/
float degToRad(float angle){
    return (angle*2*M_PI)/360;
}

/**
 * Generates a random integer between two values (included).
 * @param lower Lower bound
 * @param upper Upper bound
 * @return Random integer
*/
int randInt(int lower, int upper){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

/**
 * Gets the position pointed at the edge of the frame from the center.
 * This function is mainly used for the placement of asteroids at the beginning of the game.
 * 
 * @param angle Angle of the entity. Must be in degrees and between 0° and 360°
 * @param frame Raw pointer of the frame
 * @return Position on at the edge of the frame
*/
sf::Vector2f getBorder(float angle, Frame *frame){
    // The frame is delimited in 4 zones forming an X with the upper left segment as the origin for the angle.
    // The coordinate system must therefore be inclined by 45°:
    float refAngle = fmod((angle + 45), 360); 

    int size = (*frame).getSize();
    // Formula for each zone:
    if (refAngle <= 90){
        return sf::Vector2f((size/2)*(1+tan(degToRad(angle))),0);
    } else if (refAngle <= 180){
        return sf::Vector2f(size,(size/2)*(1-tan(degToRad(90-angle))));
    } else if (refAngle <= 270){
        return sf::Vector2f((size/2)*(1-tan(degToRad(angle))),size);
    } else {
        return sf::Vector2f(0,(size/2)*(1+tan(degToRad(270-angle))));
    }
}

Frame::Frame(int size){
    this->size = size;
    origin = sf::Vector2i(0, 0);
    border = sf::VertexArray(sf::LineStrip, 5);
    updateBorder();
}

/**
 * Updates the border of the frame.
*/
void Frame::updateBorder(){
    border[0] = sf::Vertex(sf::Vector2f(origin.x, origin.y));
    border[1] = sf::Vertex(sf::Vector2f(origin.x+size, origin.y));
    border[2] = sf::Vertex(sf::Vector2f(origin.x+size, origin.y+size));
    border[3] = sf::Vertex(sf::Vector2f(origin.x, origin.y+size));
    border[4] = border[0];
}

void Frame::setSize(int s){
    size = s;
    updateBorder();
}

int Frame::getSize(){
    return size;
}

sf::Vector2i Frame::getOrigin(){
    return origin;
}

void Frame::setOrigin(float x, float y){
    origin.x = x;
    origin.y = y;
    updateBorder();
}

sf::VertexArray Frame::getBorder(){
    return border;
}

void playSound(const sf::SoundBuffer buffer){
    sf::Sound * sound = new sf::Sound();
    sound->setBuffer(buffer);
    sound->play();
    while(sound->getStatus() == sf::SoundSource::Status::Playing){

    }
    std::cout << "killed" << std::endl;
    delete(sound);
}