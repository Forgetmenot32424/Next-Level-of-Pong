#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    sf::RectangleShape shape;
    float speed;

    Paddle(float x, float y) {
        shape.setSize(sf::Vector2f(12.f, 100.f));
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(6.f, 50.f);
        shape.setPosition(x, y);
        speed = 6.f;
    }

    void moveUp() {
        shape.move(0.f, -speed);
    }

    void moveDown() {
        shape.move(0.f, speed);
    }
};

#endif
