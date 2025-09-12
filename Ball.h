#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Paddle.h"
#include "Wall.h"
#include "Sound.h"

class Ball {
public:
    sf::CircleShape shape;
    float speedX;
    float speedY;
    int bounces = 0;

    Ball(float x, float y) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(10.f, 10.f);
        shape.setPosition(x, y);

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        reset();
    }

    void reset() {
        shape.setPosition(960.f, 540.f);
        int dirX = (std::rand() % 2 == 0) ? 1 : -1;
        int dirY = (std::rand() % 2 == 0) ? 1 : -1;
        speedX = 7.f * dirX;
        speedY = 5.f * dirY;
        bounces = 0;
    }

    void update(int winW, int winH,
                const Paddle& left, const Paddle& right,
                const Wall& wall,
                int& scoreL, int& scoreR,
                Sfx& sfx)
    {
        shape.move(speedX, speedY);
        if (shape.getPosition().y - shape.getRadius() <= 0.f ||
            shape.getPosition().y + shape.getRadius() >= winH) {
            speedY = -speedY;
            sfx.playWall();
        }

        if (shape.getGlobalBounds().intersects(left.shape.getGlobalBounds())) {
            speedX = std::abs(speedX);
            ++bounces;
            increaseSpeedIfNeeded();
            sfx.playBounces();
            shape.setPosition(left.shape.getPosition().x + left.shape.getSize().x * 0.5f + shape.getRadius() + 0.5f,
                              shape.getPosition().y);
        }
        if (shape.getGlobalBounds().intersects(right.shape.getGlobalBounds())) {
            speedX = -std::abs(speedX);
            ++bounces;
            increaseSpeedIfNeeded();
            sfx.playBounces();
            shape.setPosition(right.shape.getPosition().x - right.shape.getSize().x * 0.5f - shape.getRadius() - 0.5f,
                              shape.getPosition().y);
        }

        if (shape.getGlobalBounds().intersects(wall.shape.getGlobalBounds())) {
            speedX = -speedX;
            ++bounces;
            increaseSpeedIfNeeded();
            sfx.playWall();
            sfx.playBounces();
            if (speedX > 0)
                shape.setPosition(wall.shape.getPosition().x + wall.shape.getSize().x * 0.5f + shape.getRadius() + 0.5f,
                                  shape.getPosition().y);
            else
                shape.setPosition(wall.shape.getPosition().x - wall.shape.getSize().x * 0.5f - shape.getRadius() - 0.5f,
                                  shape.getPosition().y);
        }

        if (shape.getPosition().x < 0.f) {
            ++scoreR;
            sfx.playPoints();
            reset();
            shape.setPosition(winW / 2.f, winH / 2.f);
        }
        if (shape.getPosition().x > winW) {
            ++scoreL;
            sfx.playPoints();
            reset();
            shape.setPosition(winW / 2.f, winH / 2.f);
        }
    }

private:
    void increaseSpeedIfNeeded() {
        if (bounces % 5 == 0) {
            speedX *= 1.1f;
            speedY *= 1.1f;
        }
    }
};

#endif
