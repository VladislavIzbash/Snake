#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Renderer {
public:
    explicit Renderer(sf::RenderWindow& window);

    void drawAll();

private:
    sf::RenderWindow& m_window;

};
