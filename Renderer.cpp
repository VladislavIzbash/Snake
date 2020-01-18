#include "Renderer.h"


Renderer::Renderer(sf::RenderWindow &window):
    m_window(window) {}


void Renderer::drawBackground()
{
    m_window.clear(sf::Color::Green);
}

void Renderer::drawAll() {
    drawBackground();

    m_window.display();
}

