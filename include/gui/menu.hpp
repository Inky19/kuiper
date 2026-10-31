#ifndef MENU_HPP
#define MENU_HPP

#include "utils.hpp"
#include <vector>
#include "menuElements.hpp"
#include "assetsLoader.hpp"

class Menu {
    public:
        virtual void update() = 0;
        virtual void render();
        virtual ~Menu() {};
        void initMenuElements();

    protected:
        void handleEvent(std::optional<sf::Event> event);
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
        void update();
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
        void update();
        bool isPaused(){return paused;};
        void pause(){paused = !paused;};
        bool isExit(){return exit;};
        void setExit(bool exit){this->exit = exit;};
    private:
        bool paused;
        bool exit;
};


#endif