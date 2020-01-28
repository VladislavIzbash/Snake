#include "Game.h"
#include "Util/Config.h"

#include <thread>


std::mutex g_updateLock;

Game::Game(INetwork &network): m_network(network)
{
    m_network.initEntityList(m_entityList);

    (new std::thread(&Game::mainLoop, this))->detach();
}


void Game::mainLoop()
{
    while (true) {

        for (auto& entity: m_entityList) {
            entity->update();
        }

        m_network.updateEntityList(m_entityList);

        std::this_thread::sleep_for(std::chrono::milliseconds(cfg::UPDATE_INTERVAL_MS));
    }
}

std::vector<std::unique_ptr<Entity>>& Game::getEntities() {
    return m_entityList;
}


void Game::turnLocalPlayer(Direction dir)
{
    dynamic_cast<Snake&>(m_network.getMyPlayer(m_entityList)).turn(dir);
}

sf::Color Game::pickNextColor()
{
    static unsigned int m_counter = 0;
    const std::vector<sf::Color> color_pool {
            sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Black, sf::Color::Black, sf::Color::Yellow
    };

    return color_pool.at( m_counter++ % color_pool.size());
}
