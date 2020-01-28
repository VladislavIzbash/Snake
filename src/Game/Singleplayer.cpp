#include "Singleplayer.h"


Singleplayer::Singleplayer(): m_world(false)
{
    m_world.trySpawnSnake(0);
}

void Singleplayer::update()
{
    for (auto& entity: m_world.getAllEntities()) {
        entity->update();
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


