#pragma once

#include <SFML/Network/Packet.hpp>

#include <memory>
#include "Util.h"


class Entity;

class World {
public:
    explicit World(bool is_remote);

    bool isRemote() const;

    void toPacket(sf::Packet& packet) const;
    void fromPacket(sf::Packet& packet);

    std::vector<std::unique_ptr<Entity>>& getAllEntities();
    Entity& getEntityById(unsigned int id);
    void removeEntityById(unsigned int id);

    bool trySpawnSnake(unsigned int id);

private:
    const bool m_isRemote;
    std::vector<std::unique_ptr<Entity>> m_entityList;

};