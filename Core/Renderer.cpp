#include "Renderer.h"

#include "../BaseObjects/Snake.h"
#include "../Settings.h"


Renderer::Renderer(sf::RenderWindow &window): m_window(window) {}

void Renderer::drawAll() {
    m_window.clear(settings::BACKGROUND_COLOR);

    m_window.display();
}

