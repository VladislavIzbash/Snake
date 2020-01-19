#include "Renderer.h"


Renderer::Renderer(sf::RenderWindow &window):
    m_window(window),
    m_background(sf::Vector2f(0.0, 0.0), window.getSize(), sf::Color(0, 220, 0)) {}


void Renderer::drawAll() {
    m_window.draw(m_background.getDrawable());

    m_window.display();
}

