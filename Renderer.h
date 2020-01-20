#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"

class Renderer {
public:
    explicit Renderer(sf::RenderWindow& window, Game& game);

    void drawAll();

private:
    sf::RenderWindow& m_window;
    Game& m_game;
};
