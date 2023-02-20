#ifndef MENU_HPP
#define MENU_HPP

#include "utils.hpp"
#include <vector>

class TextElement : public sf::Text {
    public:
        TextElement();
        TextElement(std::string value, float xRelative, float yRelative, float relativeSize);
        void place(sf::Vector2u windowSize);
        float getRelativeSize();
    private:
        sf::Vector2f relativePosition;
        float relativeSize;
};


class MainMenu {
    public:
        MainMenu(sf::RenderWindow * window, Frame * frame);
        void update(sf::Event * event);
        void render();
        
    private:
        Frame * frame;
        sf::Font font;
        sf::RenderWindow * window;
        std::vector<TextElement> texts;
};



#endif