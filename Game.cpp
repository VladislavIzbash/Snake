#include "Game.h"
#include "Settings.h"

#include <thread>
#include <SFML/Window/Event.hpp>


Game::Game(INetwork &network): m_network(network)
{
    m_network.initObjectList(m_object_list);

    (new std::thread(&Game::mainLoop, this))->detach();
}


void Game::mainLoop()
{
    while (true) {
        for (auto& obj: m_object_list) {
            obj->update();
        }

        m_network.update(m_object_list);

        std::this_thread::sleep_for(std::chrono::milliseconds(settings::UPDATE_INTERVAL_MS));
    }
}

GridPos Game::mapToGrid(sf::Vector2f pos)
{
    GridPos grid_pos = {
            (unsigned char)(pos.x / settings::CELL_SIZE),
            (unsigned char)(pos.y / settings::CELL_SIZE)
    };
    return grid_pos;
}

sf::Vector2f Game::mapToWorld(GridPos grid_pos)
{
    return sf::Vector2f(grid_pos.col * settings::CELL_SIZE, grid_pos.row * settings::CELL_SIZE);
}

std::vector<std::unique_ptr<GameObject>>& Game::getObjects() { return m_object_list; }

sf::Color Game::pickNextColor()
{
    static unsigned int m_counter = 0;
    const std::vector<sf::Color> color_pool {
            sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Black, sf::Color::Black, sf::Color::Yellow
    };

    return color_pool.at( m_counter++ % color_pool.size());
}

void Game::turnLocalPlayer(Snake::Direction dir)
{
    dynamic_cast<Snake&>(m_network.getMyPlayer(m_object_list)).turn(dir);
}
