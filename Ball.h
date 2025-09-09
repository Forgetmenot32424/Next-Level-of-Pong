#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Ball {
public:
    sf::CircleShape shape;
    float speedX;
    float speedY;

    Ball(float x, float y) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(10.f, 10.f);
        shape.setPosition(x, y);

        srand(static_cast<unsigned>(time(nullptr)));
        reset();
    }

    void reset() {
        shape.setPosition(400.f, 300.f);

        int dirX = (rand() % 2 == 0) ? 1 : -1;
        int dirY = (rand() % 2 == 0) ? 1 : -1;

        speedX = 5.f * dirX;
        speedY = 3.f * dirY;
    }

    void move() {
        shape.move(speedX, speedY);
    }
};
