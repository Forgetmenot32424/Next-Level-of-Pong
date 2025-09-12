#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall {
public:
    sf::RectangleShape shape;
    float speed = 6.f;
    int   dir   = 1;

    Wall(float x, float y) {
        shape.setSize(sf::Vector2f(10.f, 120.f));
        shape.setOrigin(shape.getSize().x * 0.5f, shape.getSize().y * 0.5f);
        shape.setFillColor(sf::Color(160, 160, 160));
        shape.setPosition(x, y);
    }

    void update(int windowHeight) {
        shape.move(0.f, speed * dir);

        const float halfH = shape.getSize().y * 0.5f;
        auto pos = shape.getPosition();

        if (pos.y - halfH <= 0.f) {
            pos.y = halfH;
            dir = 1;
        } else if (pos.y + halfH >= windowHeight) {
            pos.y = windowHeight - halfH;
            dir = -1;
        }
        shape.setPosition(pos);
    }
};

#endif
