#include "Renderer.h"
#include "Util/Config.h"
#include "Game.h"


Renderer::Renderer(sf::RenderWindow &window, Game& game): m_window(window), m_game(game) {}

void Renderer::drawAll() {
    m_window.clear(cfg::BACKGROUND_COLOR);

    for (auto& entity: m_game.getEntities()) {
        m_window.draw(*entity);
    }

    m_window.display();
}

