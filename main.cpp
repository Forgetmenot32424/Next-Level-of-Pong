#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"
#include "Wall.h"

int main()
{
    const int WIDTH = 1920;

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const int HEIGHT = desktop.height - 60;

    sf::RenderWindow window(
        sf::VideoMode(WIDTH, HEIGHT),
        "NEXT_LEVEL_OF_PONG",
        sf::Style::Titlebar | sf::Style::Close
        );
    window.setFramerateLimit(60);
    const int posX = (desktop.width - WIDTH) / 2;
    window.setPosition(sf::Vector2i(posX, 0));

    Paddle leftPaddle(30.f, HEIGHT / 2.f);
    Paddle rightPaddle(WIDTH - 30.f, HEIGHT / 2.f);
    Ball   ball(WIDTH / 2.f, HEIGHT / 2.f);
    Wall   wall(WIDTH / 2.f, HEIGHT / 2.f);

    int    scoreLeft  = 0;
    int    scoreRight = 0;

    Score score(WIDTH, HEIGHT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
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
        leftPaddle.update(HEIGHT);
        rightPaddle.update(HEIGHT);

        wall.update(HEIGHT);

        ball.update(WIDTH, HEIGHT, leftPaddle, rightPaddle, wall, scoreLeft, scoreRight);

        score.update(scoreLeft, scoreRight, ball.bounces);

        window.clear(sf::Color::Black);
        window.draw(leftPaddle.shape);
        window.draw(rightPaddle.shape);
        window.draw(wall.shape);
        window.draw(ball.shape);
        score.draw(window);
        window.display();
    }

    return 0;
}
