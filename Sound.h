#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Sfx {
public:
    Sfx() {
        const char* WALL   = "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/wallsound.wav";
        const char* POINTS = "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/pointsound.wav";
        const char* BOUNCE = "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/ballsound.wav";
        const char* MUSIC  = "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/gamemusic.wav";

        loadBuffer(wallBuf,   WALL,   "wall");
        loadBuffer(pointsBuf, POINTS, "points");
        loadBuffer(bounceBuf, BOUNCE, "bounce");

        wall.setBuffer(wallBuf);
        points.setBuffer(pointsBuf);
        bounces.setBuffer(bounceBuf);

        wall.setVolume(100.f);
        points.setVolume(70.f);
        bounces.setVolume(70.f);

        if (!music.openFromFile(MUSIC)) {
            std::cout << "[Sfx] Nie udalo sie wczytac muzyki: " << MUSIC << "\n";
        } else {
            music.setLoop(true);
            music.setVolume(30.f);
            music.play();
        }
    }

    void playWall()    { if (wallBuf.getSampleCount())    wall.play(); }
    void playPoints()  { if (pointsBuf.getSampleCount())  points.play(); }
    void playBounces() { if (bounceBuf.getSampleCount())  bounces.play(); }


private:
    sf::SoundBuffer wallBuf, pointsBuf, bounceBuf;
    sf::Sound wall, points, bounces;
    sf::Music music;

    static void loadBuffer(sf::SoundBuffer& buf, const std::string& path, const char* name) {
        if (!buf.loadFromFile(path)) {
            std::cout << "[Sfx] Nie udalo sie wczytac efektu (" << name << "): " << path << "\n";
        }
    }
};

#endif
