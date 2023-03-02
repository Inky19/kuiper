#include "menu.hpp"
#include "assetsLoader.hpp"
#include <iostream>
#include "utils.hpp"
#include "menuElements.hpp"

MainMenu::MainMenu(sf::RenderWindow * window, Frame * frame){
    start = false;
    this->window = window;
    this->frame = frame;
    font = Assets::millimetre;
    texts.resize(1);
    texts[0] = TextElement("Kuiper", 0.5, 0.2, 0.1);
    texts[0].setFont(font);
    texts[0].place(window->getSize());
    menuElements.push_back(&texts[0]);
    
    buttons.resize(3);
    buttons[0] = Button("Play", 0.5, 0.5, 0.05);
    buttons[1] = Button("Options", 0.5, 0.7, 0.05);
    buttons[2] = Button("Quit", 0.5, 0.9, 0.05);

    for (int i=0; i<buttons.size(); i++){
        buttons[i].setFont(font);
        buttons[i].setCharacterSize(200);
        menuElements.push_back(&buttons[i]);
    }
}

void MainMenu::update(sf::Event * event){
    float size;
    sf::FloatRect visibleArea;
    while ((*window).pollEvent(*event)){
        switch (event->type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                visibleArea = sf::FloatRect(0, 0, event->size.width, event->size.height);
                size = std::min(event->size.width, event->size.height);
                frame->setSize(size);
                (*window).setView(sf::View(visibleArea));
                frame->setOrigin((event->size.width-size)/2,(event->size.height-size)/2);
                for (int i=0; i<menuElements.size(); i++){
                    menuElements[i]->setCharacterSize(size*menuElements[i]->getRelativeSize());
                    menuElements[i]->place(window->getSize());
                }
                break;
            case sf::Event::MouseMoved:
                for (int i=0; i<buttons.size(); i++){
                    buttons[i].updateCursor(sf::Mouse::getPosition(*window), false);
                }
                break;
            case sf::Event::MouseButtonPressed:
                for (int i=0; i<buttons.size(); i++){
                        buttons[i].updateCursor(sf::Mouse::getPosition(*window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                    }
                break;
        }
    }
    render();
    for (int i=0; i<buttons.size(); i++){
        if(buttons[i].isClicked()){
            switch (i)
            {
            case 0:
                start = true;
                break;
            
            case 1:
                std::cout << "UwU" << std::endl;
                break;
            
            case 2:
                window->close();
                break;
            
            default:
                break;
            }
        }
    }
}

void MainMenu::render(){
    window->clear();
    window->draw(frame->getBorder());
    for (sf::Text text: texts){
        window->draw(text);
    }
    for (int i=0; i<buttons.size(); i++){
        buttons[i].draw(window);
    }
    window->display();
}

bool MainMenu::isStarting(){
    return start;
}