#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

int main()
{
    const int WIDTH  = 800;
    const int HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "NEXT_LEVEL_OF_PONG");
    window.setFramerateLimit(60);

    Paddle leftPaddle(30.f, HEIGHT / 2);
    Paddle rightPaddle(WIDTH - 30.f, HEIGHT / 2);
    Ball ball(WIDTH / 2, HEIGHT / 2);

    int scoreLeft = 0;
    int scoreRight = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddle.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddle.moveDown();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rightPaddle.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rightPaddle.moveDown();

        ball.move();

        if (ball.shape.getPosition().y - 10 <= 0 || ball.shape.getPosition().y + 10 >= HEIGHT)
            ball.speedY = -ball.speedY;
        if (ball.shape.getGlobalBounds().intersects(leftPaddle.shape.getGlobalBounds()))
            ball.speedX = std::abs(ball.speedX);
        if (ball.shape.getGlobalBounds().intersects(rightPaddle.shape.getGlobalBounds()))
            ball.speedX = -std::abs(ball.speedX);
        if (ball.shape.getPosition().x < 0) {
            scoreRight++;
            ball.reset();
        }
        if (ball.shape.getPosition().x > WIDTH) {
            scoreLeft++;
            ball.reset();
        }
        window.clear(sf::Color::Black);
        window.draw(leftPaddle.shape);
        window.draw(rightPaddle.shape);
        window.draw(ball.shape);
        window.display();
    }

    return 0;
}
