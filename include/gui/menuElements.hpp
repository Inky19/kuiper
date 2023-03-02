#ifndef MENUELEMENTS_HPP
#define MENUELEMENTS_HPP

#include "utils.hpp"

class TextElement : public sf::Text {
    public:
        TextElement();
        TextElement(std::string value, float xRelative, float yRelative, float relativeSize);
        void place(sf::Vector2u windowSize);
        float getRelativeSize();
    protected:
        sf::Vector2f relativePosition;
        float relativeSize;
};

class Button : public TextElement {
    public:
        Button();
        Button(std::string value, float xRelative, float yRelative, float relativeSize);
        bool isClicked();
        void setClicked(bool clicked);
        bool isHover();
        void updateCursor(sf::Vector2i cursor, bool clicked);
        void setHover(bool hover);
        void draw(sf::RenderWindow * window);
    private:
        bool clicked;
        bool hover;
        sf::RectangleShape border;
};

#endif