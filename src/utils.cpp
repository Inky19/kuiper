#include <math.h>
#include <random>
#include "utils.hpp"

Entity::~Entity() {}; // Destructor from a child child class also calls destructor from super class (must be defined)

sf::Sprite Entity::getSprite(){
    return sprite;
}

float degToRad(float angle){
    return (angle*2*M_PI)/360;
}

int randInt(int lower, int upper){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(lower, upper);
    return distr(gen);
}

sf::Vector2f getBorder(float angle, Frame *frame){
    float refAngle = fmod((angle + 45), 360);
    int size = (*frame).getSize();
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
    origin = sf::Vector2i(0,0);
    border = sf::VertexArray(sf::LineStrip, 5);
    updateBorder();
}

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