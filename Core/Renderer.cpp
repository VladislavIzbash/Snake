#include "Renderer.h"

#include "../BaseObjects/Snake.h"


Renderer::Renderer(sf::RenderWindow &window):
    m_window(window),
    m_background(sf::Vector2f(0.0, 0.0), window.getSize(), sf::Color(0, 220, 0))
{}

void Renderer::drawAll() {
    m_background.draw(m_window);

    m_window.display();
}

