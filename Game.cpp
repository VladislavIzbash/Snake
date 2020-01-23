#include "Game.h"
#include "Settings.h"

#include <thread>


Game::Game(INetwork &network): m_network(network)
{
    m_network.initObjectList(m_object_list);

    (new std::thread(&Game::mainLoop, this))->detach();
}


void Game::mainLoop()
{
    while (true) {
        m_network.update(m_object_list);

        std::this_thread::sleep_for(std::chrono::seconds(1 / settings::TICKS_PER_SECOND));
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
