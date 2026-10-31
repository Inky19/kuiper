#include "menuElements.hpp"
#include "assetsLoader.hpp"

#include <iostream>

TextElement::TextElement() : sf::Text(Assets::millimetre) {
    this->setString("");
    relativePosition = sf::Vector2f(0,0);
    relativeSize = 0;
}

TextElement::TextElement(std::string value, float xRelative, float yRelative, float relativeSize) : sf::Text(Assets::millimetre){
    this->setString(value);
    relativePosition = sf::Vector2f(xRelative,yRelative);
    this->relativeSize = relativeSize;
}

/**
 * Places a TextElement in a window, using its relative coordinates.
 * @param windowSize Size of the window
 */
void TextElement::place(sf::Vector2u windowSize){
    
    sf::Vector2f center = { getGlobalBounds().size.x/2.f, getGlobalBounds().size.y/2.f};
    sf::Vector2f localBounds = { getLocalBounds().position.x, getLocalBounds().position.y};
    setOrigin(center + localBounds);
    setPosition({windowSize.x*relativePosition.x, windowSize.y*relativePosition.y});
}

float TextElement::getRelativeSize(){
    return relativeSize;
}

Button::Button(){
    clicked = false;
    border.setOutlineThickness(2);
    border.setSize(sf::Vector2f(100,100));
    border.setFillColor(sf::Color(0,0,0,0));
}

Button::Button(std::string value, float xRelative, float yRelative, float relativeSize) : TextElement(value, xRelative, yRelative, relativeSize){
    clicked = false;
    border.setOutlineThickness(2);
    border.setSize(sf::Vector2f(100,100));
    border.setFillColor(sf::Color(0,0,0,0));
};

void Button::draw(sf::RenderWindow * window){
    window->draw(*this);
    border.setSize(sf::Vector2f(this->getLocalBounds().size.x+30, this->getLocalBounds().size.y+15));
    sf::FloatRect dim = border.getLocalBounds();
    border.setOrigin({dim.size.x/2, dim.size.y/2});
    border.setPosition(this->getPosition());
    
    window->draw(border);
}

void Button::updateCursor(sf::Vector2i cursor, bool clicked){
    sf::Vector2f pos = border.getPosition();
    sf::FloatRect dim = border.getLocalBounds();
    float dx = pos.x-cursor.x;
    float dy = pos.y-cursor.y;
    if (abs(dx) < dim.size.x/2 && abs(dy) < dim.size.y/2 ){
        border.setOutlineColor(sf::Color(255, 255, 0));
        setFillColor(sf::Color(255, 255, 0));
        this->clicked = clicked;
    } else {
        border.setOutlineColor(sf::Color(255, 255, 255));
        setFillColor(sf::Color(255, 255, 255));
    }
}

void Button::setHover(bool hover){this->hover = hover;}
bool Button::isHover(){return hover;}
void Button::setClicked(bool clicked){this->clicked = clicked;}
bool Button::isClicked(){return clicked;}