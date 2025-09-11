#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <string>

class Score {
public:
    sf::Font font;
    sf::Text leftScoreText;
    sf::Text rightScoreText;
    sf::Text bounceCountText;

    Score(int winW, int winH) {
        font.loadFromFile("C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/Sakamoto.ttf");

        float top = winH * 0.05f;

        leftScoreText.setFont(font);
        leftScoreText.setCharacterSize(60);
        leftScoreText.setFillColor(sf::Color::White);
        leftScoreText.setString("0");
        leftScoreText.setPosition(winW / 4.f, top);

        rightScoreText.setFont(font);
        rightScoreText.setCharacterSize(60);
        rightScoreText.setFillColor(sf::Color::White);
        rightScoreText.setString("0");
        rightScoreText.setPosition(3 * winW / 4.f, top);

        bounceCountText.setFont(font);
        bounceCountText.setCharacterSize(100);
        bounceCountText.setFillColor(sf::Color::Yellow);
        bounceCountText.setString("0");
        bounceCountText.setPosition(winW / 2.f - 50.f, top - 10.f);
    }

    void update(int leftScore, int rightScore, int bounceCount) {
        leftScoreText.setString(std::to_string(leftScore));
        rightScoreText.setString(std::to_string(rightScore));
        bounceCountText.setString(std::to_string(bounceCount));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(leftScoreText);
        window.draw(rightScoreText);
        window.draw(bounceCountText);
    }
};

#endif
