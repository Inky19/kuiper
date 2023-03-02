#ifndef MENU_HPP
#define MENU_HPP

#include "utils.hpp"
#include <vector>
#include "menuElements.hpp"

class MainMenu {
    public:
        MainMenu(sf::RenderWindow * window, Frame * frame);
        void update(sf::Event * event);
        void render();
        bool isStarting();
        
    private:
        bool start;
        Frame * frame;
        sf::Font font;
        sf::RenderWindow * window;
        std::vector<TextElement> texts;
        std::vector<Button> buttons;
        std::vector<TextElement*> menuElements;
};



#endif