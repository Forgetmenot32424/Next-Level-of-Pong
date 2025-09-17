#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
public:
    sf::RectangleShape shape;

    Paddle(float x, float y) {
        shape.setSize(sf::Vector2f(WIDTH_PX, HEIGHT_PX));
        shape.setOrigin(shape.getSize().x * 0.5f, shape.getSize().y * 0.5f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);

        currentSpeed = BASE_SPEED;
    }

    void moveUp()   { shape.move(0.f, -currentSpeed); }
    void moveDown() { shape.move(0.f,  currentSpeed); }

    void update(int windowHeight) {
        float halfH = shape.getSize().y * 0.5f;
        sf::Vector2f pos = shape.getPosition();
        if (pos.y - halfH < 0.f)          pos.y = halfH;
        if (pos.y + halfH > windowHeight) pos.y = windowHeight - halfH;
        shape.setPosition(pos);
        if (sizeActive && sizeClock.getElapsedTime().asSeconds() > POWER_DURATION_S) {
            deactivateSizePowerUp();
            sizeCooldownClock.restart();
        }
        if (speedActive && speedClock.getElapsedTime().asSeconds() > POWER_DURATION_S) {
            deactivateSpeedPowerUp();
            speedCooldownClock.restart();
        }

        if (!canUseSize && !sizeActive && sizeCooldownClock.getElapsedTime().asSeconds() > COOLDOWN_S) {
            canUseSize = true;
        }
        if (!canUseSpeed && !speedActive && speedCooldownClock.getElapsedTime().asSeconds() > COOLDOWN_S) {
            canUseSpeed = true;
        }
    }

    void activateSizePowerUp() {
        if (!sizeActive && canUseSize) {
            shape.setSize(sf::Vector2f(WIDTH_PX, HEIGHT_PX * 2.f));
            shape.setOrigin(shape.getSize().x * 0.5f, shape.getSize().y * 0.5f);
            sizeClock.restart();
            sizeActive = true;
            canUseSize = false;
        }
    }
    bool isSizeReady() const { return canUseSize; }

    void activateSpeedPowerUp() {
        if (!speedActive && canUseSpeed) {
            currentSpeed = BASE_SPEED * SPEED_MULT;
            speedClock.restart();
            speedActive = true;
            canUseSpeed = false;
        }
    }
    bool isSpeedReady() const { return canUseSpeed; }

private:
    static constexpr float POWER_DURATION_S = 10.f;
    static constexpr float COOLDOWN_S       = 25.f;
    static constexpr float WIDTH_PX         = 20.f;
    static constexpr float HEIGHT_PX        = 100.f;
    static constexpr float SPEED_MULT       = 2.f;
    static constexpr float BASE_SPEED       = 8.f;

    bool      sizeActive = false;
    bool      canUseSize = true;
    sf::Clock sizeClock;
    sf::Clock sizeCooldownClock;

    bool      speedActive = false;
    bool      canUseSpeed = true;
    sf::Clock speedClock;
    sf::Clock speedCooldownClock;

    float currentSpeed = BASE_SPEED;

    void deactivateSizePowerUp() {
        shape.setSize(sf::Vector2f(WIDTH_PX, HEIGHT_PX));
        shape.setOrigin(shape.getSize().x * 0.5f, shape.getSize().y * 0.5f);
        sizeActive = false;
    }
    void deactivateSpeedPowerUp() {
        currentSpeed = BASE_SPEED;
        speedActive = false;
    }
};

#endif
