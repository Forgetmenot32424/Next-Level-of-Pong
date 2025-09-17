#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"
#include "Wall.h"
#include "Sound.h"
#include "Theme.h"

static void centerText(sf::Text& t, float cx, float cy) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
    t.setPosition(cx, cy);
}

enum class GameState { Menu, Playing, GameOver };

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
    Sfx    sfx;

    int scoreLeft  = 0;
    int scoreRight = 0;
    Score score(WIDTH, HEIGHT);

    sf::Texture powerTexSize, powerTexSpeed;
    powerTexSize.loadFromFile ("C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/powerup.png");
    powerTexSpeed.loadFromFile("C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/powerup2.png");

    sf::Sprite leftIconSize(powerTexSize), rightIconSize(powerTexSize);
    leftIconSize.setScale(0.5f, 0.5f);
    rightIconSize.setScale(0.5f, 0.5f);
    leftIconSize.setPosition(50.f, 20.f);
    rightIconSize.setPosition(WIDTH - 50.f - powerTexSize.getSize().x * 0.5f, 20.f);

    sf::Sprite leftIconSpeed(powerTexSpeed), rightIconSpeed(powerTexSpeed);
    leftIconSpeed.setScale(0.11f, 0.11f);
    rightIconSpeed.setScale(0.11f, 0.11f);
    float marginBottom = 10.f;
    float leftSpeedY  = HEIGHT - marginBottom - powerTexSpeed.getSize().y * 0.11f;
    float rightSpeedY = HEIGHT - marginBottom - powerTexSpeed.getSize().y * 0.11f;
    leftIconSpeed.setPosition(leftIconSize.getPosition().x, leftSpeedY);
    rightIconSpeed.setPosition(rightIconSize.getPosition().x, rightSpeedY);

    sf::Font font;
    font.loadFromFile("C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/Sakamoto.ttf");


    sf::Text title("NEXT LEVEL OF PONG", font, 100);
    sf::Text startMsg("Press ENTER to Start", font, 50);
    centerText(title, WIDTH * 0.5f, HEIGHT * 0.5f - 100.f);
    centerText(startMsg, WIDTH * 0.5f, HEIGHT * 0.5f + 50.f);

    sf::Text winText;
    winText.setFont(font);
    winText.setCharacterSize(120);
    winText.setFillColor(sf::Color::Yellow);
    winText.setStyle(sf::Text::Bold);

    GameState state = GameState::Menu;

    auto resetGame = [&]() {
        scoreLeft = 0;
        scoreRight = 0;

        leftPaddle  = Paddle(30.f, HEIGHT / 2.f);
        rightPaddle = Paddle(WIDTH - 30.f, HEIGHT / 2.f);
        wall        = Wall(WIDTH / 2.f, HEIGHT / 2.f);

        ball.reset();
        ball.shape.setPosition(WIDTH / 2.f, HEIGHT / 2.f);
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (state == GameState::Menu && event.key.code == sf::Keyboard::Enter) {
                    state = GameState::Playing;
                }
                else if (state == GameState::Playing) {
                    if (event.key.code == sf::Keyboard::Space)
                        leftPaddle.activateSizePowerUp();
                    if (event.key.code == sf::Keyboard::RShift)
                        rightPaddle.activateSizePowerUp();
                    if (event.key.code == sf::Keyboard::LShift)
                        leftPaddle.activateSpeedPowerUp();
                    if (event.key.code == sf::Keyboard::RControl)
                        rightPaddle.activateSpeedPowerUp();
                }
                else if (state == GameState::GameOver && event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    state = GameState::Playing;
                }
            }
        }

        if (state == GameState::Playing) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    leftPaddle.moveUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    leftPaddle.moveDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))   rightPaddle.moveUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) rightPaddle.moveDown();

            leftPaddle.update(HEIGHT);
            rightPaddle.update(HEIGHT);
            wall.update(HEIGHT);
            ball.update(WIDTH, HEIGHT, leftPaddle, rightPaddle, wall, scoreLeft, scoreRight, sfx);

            if (scoreLeft >= 5) {
                winText.setString("PLAYER 1 WINS!");
                centerText(winText, WIDTH * 0.5f, HEIGHT * 0.5f);
                state = GameState::GameOver;
            } else if (scoreRight >= 5) {
                winText.setString("PLAYER 2 WINS!");
                centerText(winText, WIDTH * 0.5f, HEIGHT * 0.5f);
                state = GameState::GameOver;
            }
        }
        int themeIndex = ThemeIndexFromSteps(ball.bounces);
        const auto& theme = AllThemes()[themeIndex];
        leftPaddle.shape.setFillColor(theme.paddle);
        rightPaddle.shape.setFillColor(theme.paddle);
        wall.shape.setFillColor(theme.wall);
        ball.shape.setFillColor(theme.ball);

        sf::Sprite bg = ThemeAssets::makeBackground(themeIndex, window.getSize());

        score.update(scoreLeft, scoreRight, ball.bounces);

        leftIconSize.setColor (leftPaddle.isSizeReady()    ? sf::Color(255,255,255,255) : sf::Color(255,255,255,100));
        rightIconSize.setColor(rightPaddle.isSizeReady()   ? sf::Color(255,255,255,255) : sf::Color(255,255,255,100));
        leftIconSpeed.setColor (leftPaddle.isSpeedReady()  ? sf::Color(255,255,255,255) : sf::Color(255,255,255,100));
        rightIconSpeed.setColor(rightPaddle.isSpeedReady() ? sf::Color(255,255,255,255) : sf::Color(255,255,255,100));

        window.clear();

        if (state == GameState::Menu) {
            window.draw(title);
            window.draw(startMsg);
        }
        else if (state == GameState::Playing) {
            window.draw(bg);
            window.draw(leftPaddle.shape);
            window.draw(rightPaddle.shape);
            window.draw(wall.shape);
            window.draw(ball.shape);
            score.draw(window);
            window.draw(leftIconSize);
            window.draw(rightIconSize);
            window.draw(leftIconSpeed);
            window.draw(rightIconSpeed);
        }
        else if (state == GameState::GameOver) {
            window.draw(winText);
        }

        window.display();
    }

    return 0;
}
