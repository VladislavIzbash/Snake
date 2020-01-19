#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../BaseObjects/Background.h"

class Renderer {
public:
    explicit Renderer(sf::RenderWindow& window);

    void drawAll();

private:
    sf::RenderWindow& m_window;
    Background m_background;

};
