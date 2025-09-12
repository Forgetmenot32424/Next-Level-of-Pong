#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Theme {
    sf::Color paddle;
    sf::Color wall;
    sf::Color ball;
    const char* backgroundPath;
};

inline const std::vector<Theme>& AllThemes() {
    static const std::vector<Theme> themes = {
        { sf::Color(250,250,250), sf::Color(160,160,160), sf::Color(255,230, 80), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/night.jpg" },
        { sf::Color( 80,220,200), sf::Color(220,120,120), sf::Color(240,240,240), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/ocean.jpg" },
        { sf::Color(220, 80,200), sf::Color(120,220,120), sf::Color(255,120,160), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/neon.jpg" },
        { sf::Color(200,255,200), sf::Color(255,200,100), sf::Color(120,220,120), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/forest.jpg" },
        { sf::Color(255,220,180), sf::Color(200,200,255), sf::Color(255,120, 80), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/beach.jpg" },
        { sf::Color(140,180,255), sf::Color(255,170, 60), sf::Color(255,255,255), "C:/Users/antek/OneDrive/Dokumenty/NEXT_LEVEL_OF_PONG/Resources/sky.jpg" }
    };
    return themes;
}

inline int ThemeIndexFromSteps(int steps) {
    const auto& v = AllThemes();
    int idx = (steps / 5) % static_cast<int>(v.size());
    if (idx < 0) idx = 0;
    return idx;
}

struct ThemeAssets {
    static sf::Sprite makeBackground(int themeIndex, sf::Vector2u targetSize) {
        ensureLoaded();
        themeIndex = clampIndex(themeIndex);
        sf::Sprite sp;
        sp.setTexture(textures()[themeIndex]);
        const auto& tex = textures()[themeIndex];
        sf::Vector2u ts = tex.getSize();
        if (ts.x > 0 && ts.y > 0) {
            float sx = static_cast<float>(targetSize.x) / static_cast<float>(ts.x);
            float sy = static_cast<float>(targetSize.y) / static_cast<float>(ts.y);
            sp.setScale(sx, sy);
        }
        sp.setPosition(0.f, 0.f);
        return sp;
    }

private:
    static std::vector<sf::Texture>& textures() {
        static std::vector<sf::Texture> texv;
        return texv;
    }

    static void ensureLoaded() {
        auto& texv = textures();
        if (!texv.empty()) return;

        const auto& themes = AllThemes();
        texv.resize(themes.size());
        for (std::size_t i = 0; i < themes.size(); ++i) {
            texv[i].loadFromFile(themes[i].backgroundPath);
            texv[i].setSmooth(true);
        }
    }

    static int clampIndex(int idx) {
        const auto& v = AllThemes();
        if (v.empty()) return 0;
        if (idx < 0) return 0;
        if (idx >= static_cast<int>(v.size())) return static_cast<int>(v.size()) - 1;
        return idx;
    }
};

#endif
