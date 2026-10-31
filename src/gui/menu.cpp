#include "menu.hpp"
#include "assetsLoader.hpp"
#include <iostream>
#include "utils.hpp"
#include "menuElements.hpp"

void Menu::render(){
    for (int i=0; i<texts.size(); i++){
        window->draw(texts[i]);
    }
    for (int i=0; i<buttons.size(); i++){
        buttons[i].draw(window);
    }
}

void Menu::handleEvent(std::optional<sf::Event> event){
    float size;
    sf::FloatRect visibleArea;
    if (event->is<sf::Event::Closed>()) {
        window->close();
    } else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
        visibleArea = sf::FloatRect({0, 0}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
        size = std::min(resized->size.x, resized->size.y);
        this->resize(resized->size.x, resized->size.y);
        
        (window)->setView(sf::View(visibleArea));
        for (int i=0; i<menuElements.size(); i++){
            menuElements[i]->setCharacterSize(size*menuElements[i]->getRelativeSize());
            menuElements[i]->place(window->getSize());
        }
    } else if (event->is<sf::Event::MouseMoved>()) {
        for (int i=0; i<buttons.size(); i++){
            buttons[i].updateCursor(sf::Mouse::getPosition(*window), false);
        }
    } else if (event->is<sf::Event::MouseButtonPressed>()) {
        for (int i=0; i<buttons.size(); i++){
            buttons[i].updateCursor(sf::Mouse::getPosition(*window), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
        }
    }
}

void Menu::initMenuElements(){
    menuElements.clear();
    for (int i=0; i<texts.size(); i++){
        menuElements.push_back(&texts[i]);
    }
    for (int i=0; i<buttons.size(); i++){
        menuElements.push_back(&buttons[i]);
    }
    for (int i=0; i<menuElements.size(); i++){
        menuElements[i]->setFont(font);
        int size = std::min(window->getSize().x, window->getSize().y);
        menuElements[i]->setCharacterSize(size*menuElements[i]->getRelativeSize());
        menuElements[i]->place(window->getSize());
    }
}

MainMenu::MainMenu(sf::RenderWindow * window, Frame * frame){
    start = false;
    this->window = window;
    this->frame = frame;
    font = Assets::millimetre;
    texts.resize(1);
    texts[0] = TextElement("Kuiper", 0.5, 0.2, 0.1);
    menuElements.push_back(&texts[0]);
    
    buttons.resize(2);
    buttons[0] = Button("Play", 0.5, 0.5, 0.05);
    buttons[1] = Button("Quit", 0.5, 0.7, 0.05);

    for (int i=0; i<buttons.size(); i++){
        menuElements.push_back(&buttons[i]);
    }
    initMenuElements();
}

void MainMenu::resize(int width, int height){
    int frameSize = std::min(width, height);
    frame->setSize(frameSize);
    frame->setOrigin((width-frameSize)/2,(height-frameSize)/2);
}

void MainMenu::update(){
    while (const std::optional event = window->pollEvent()){
        handleEvent(event);
    }

    render();
    if (buttons[0].isClicked()){
        start = true;
        buttons[0].setClicked(false);
    } else if (buttons[1].isClicked()){
        window->close();
        buttons[1].setClicked(false);
    }
}

void MainMenu::render(){
    window->clear();
    Menu::render();
    window->draw(frame->getBorder());
    window->display();
}

bool MainMenu::isStarting(){
    return start;
}

PauseMenu::PauseMenu(sf::RenderWindow * window){
    this->window = window;
    paused = false;
    exit = false;
    font = Assets::millimetre;
    texts.resize(1);
    texts[0] = TextElement("Pause", 0.5, 0.2, 0.1);
    
    buttons.resize(2);
    buttons[0] = Button("Continue", 0.5, 0.5, 0.05);
    buttons[1] = Button("Retry", 0.5, 0.7, 0.05);

    for (int i=0; i<buttons.size(); i++){
        buttons[i].setFont(font);
    }
}

void PauseMenu::update(){
    while (const std::optional event = window->pollEvent()){
        if (const auto * keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                paused = !paused;
            }
        } else {
            handleEvent(event);
        }
    }
    render();
    if (buttons[0].isClicked()){
        paused = false;
        buttons[0].setClicked(false);
    } else if (buttons[1].isClicked()){
        exit = true;
        buttons[1].setClicked(false);
    }
}

