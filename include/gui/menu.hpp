#ifndef MENU_HPP
#define MENU_HPP

#include "utils.hpp"
#include <vector>
#include "menuElements.hpp"
#include "assetsLoader.hpp"

class Menu {
    public:
        virtual void update(sf::Event * event) = 0;
        virtual void render();
        virtual ~Menu() {};
        void initMenuElements();

    protected:
        void handleEvent(sf::Event * event);
        virtual void resize(int width, int height){};
        sf::Font font;
        sf::RenderWindow * window;
        std::vector<TextElement> texts;
        std::vector<Button> buttons;
        std::vector<TextElement*> menuElements;
};

class MainMenu : public Menu {
    public:
        MainMenu(sf::RenderWindow * window, Frame * frame);
        void update(sf::Event * event);
        bool isStarting();
        void render() override;
    private:
        void resize(int width, int height) override;
        bool start;
        Frame * frame;
};

class PauseMenu : public Menu {
    public:
        PauseMenu(sf::RenderWindow * window);
        void update(sf::Event * event);
        bool isPaused(){return paused;};
        void pause(){paused = !paused;};
    private:
        bool paused;
};


#endif