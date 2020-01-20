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


    std::this_thread::sleep_for(std::chrono::seconds(1 / settings::TICKS_PER_SECOND));
}

Game::GridPos Game::mapToGrid(sf::Vector2f pos)
{
    GridPos grid_pos = {
            (unsigned short int)(pos.x / settings::CELL_SIZE),
            (unsigned short int)(pos.y / settings::CELL_SIZE)
    };
    return grid_pos;
}

sf::Vector2f Game::mapToWorld(Game::GridPos grid_pos)
{
    return sf::Vector2f(grid_pos.col * settings::CELL_SIZE, grid_pos.row * settings::CELL_SIZE);
}

std::vector<std::unique_ptr<IObject>>& Game::getObjects() { return m_object_list; }
