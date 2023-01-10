#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

float degToRad(float angle);

int randInt(int lower, int upper);

class Frame{
    private:
        int size;
        sf::Vector2i origin;
        sf::VertexArray border;
        void updateBorder();
    public:
        Frame(int size);
        int getSize();
        void setSize(int size);
        void setOrigin(float x, float y);
        sf::Vector2i getOrigin();
        sf::VertexArray getBorder();
};

class Entity : public sf::Transformable{
    protected:
        float mass;
        sf::Vector2f pos;
        float speed;
        float angle;
        sf::Sprite sprite;
        Frame *frame;

    public:
        virtual ~Entity() = 0;
        sf::Sprite getSprite();
};

sf::Vector2f getBorder(float angle, Frame *frame);

#endif