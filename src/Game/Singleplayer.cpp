#include "Singleplayer.h"


Singleplayer::Singleplayer(): m_world(false)
{
    m_world.trySpawnSnake(0);
}

void Singleplayer::update()
{
    static sf::Clock clock;

    for (auto& entity: m_world.getAllEntities()) {
        entity->update();
    }
    collectGarbage();

    if (clock.getElapsedTime().asMilliseconds() >= util::cfg::FRUIT_INTERVAL_MS) {
        m_world.spawnFruit();

        clock.restart();
    }
}

Snake& Singleplayer::getLocalPlayer()
{
    return dynamic_cast<Snake&>(m_world.getEntityById(0));
}

void Singleplayer::render(sf::RenderTarget& target)
{
    for (auto& entity: m_world.getAllEntities()) {
        target.draw(*entity);
    }
}

void Singleplayer::collectGarbage()
{
    std::vector<std::unique_ptr<Entity>>& entities = m_world.getAllEntities();

    for (auto entity_it = entities.begin(); entity_it != entities.end();) {
        if (entity_it->get()->isDead()) entities.erase(entity_it);
        else entity_it++;
    }
}


