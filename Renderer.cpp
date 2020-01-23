#include "Renderer.h"
#include "Settings.h"
#include "Game.h"


Renderer::Renderer(sf::RenderWindow &window, Game& game): m_window(window), m_game(game) {}

void Renderer::drawAll() {
    m_window.clear(settings::BACKGROUND_COLOR);

    for (std::unique_ptr<GameObject>& obj: m_game.getObjects()) {
        obj->draw(m_window);
    }

    m_window.display();
}

