#include "menu.hpp"
#include "assetsLoader.hpp"
#include <iostream>
#include "utils.hpp"

TextElement::TextElement(){
    this->setString("");
    relativePosition = sf::Vector2f(0,0);
    relativeSize = 0;
}

TextElement::TextElement(std::string value, float xRelative, float yRelative, float relativeSize){
    this->setString(value);
    relativePosition = sf::Vector2f(xRelative,yRelative);
    this->relativeSize = relativeSize;
}

/**
 * Places a TextElement in a window, using its relative coordinates.
 * @param windowSize Size of the window
 */
void TextElement::place(sf::Vector2u windowSize){
    sf::Vector2f center = { getGlobalBounds().width/2.f, getGlobalBounds().height/2.f};
    sf::Vector2f localBounds = { getLocalBounds().left, getLocalBounds().top};
    setOrigin(center + localBounds);
    setPosition(windowSize.x*relativePosition.x, windowSize.y*relativePosition.y);
}

float TextElement::getRelativeSize(){
    return relativeSize;
}

MainMenu::MainMenu(sf::RenderWindow * window, Frame * frame){
    this->window = window;
    this->frame = frame;
    font = Assets::millimetre;
    texts.resize(4);
    texts[0] = TextElement("Kuiper", 0.5, 0.2, 0.1);
    texts[1] = TextElement("Play", 0.5, 0.5, 0.05);
    texts[2] = TextElement("Options", 0.5, 0.7, 0.05);
    texts[3] = TextElement("Quit", 0.5, 0.9, 0.05);

    for (int i=0; i<texts.size(); i++){
        texts[i].setFont(font);
        texts[i].setCharacterSize(200);
    }
    texts[0].place(window->getSize());
}

void MainMenu::update(sf::Event * event){
    while ((*window).pollEvent(*event)){
        switch (event->type){
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, event->size.width, event->size.height);
                float size = std::min(event->size.width, event->size.height);
                frame->setSize(size);
                (*window).setView(sf::View(visibleArea));
                frame->setOrigin((event->size.width-size)/2,(event->size.height-size)/2);
                for (int i=0; i<texts.size(); i++){
                    texts[i].setCharacterSize(size*texts[i].getRelativeSize());
                    texts[i].place(window->getSize());
                }
                break;
        }
    }

    render();
}

void MainMenu::render(){
    window->clear();
    window->draw(frame->getBorder());
    for (sf::Text text: texts){
        window->draw(text);
    }
    window->display();
}