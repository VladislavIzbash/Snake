#include "World.h"

#include "Util.h"
#include "Entity/Snake.h"


World::World(bool is_remote): m_isRemote(is_remote) {}

bool World::isRemote() const { return m_isRemote; }

void World::toPacket(sf::Packet& packet) const
{
    packet << (sf::Uint16)m_entityList.size();

    for (auto& entity: m_entityList) {
        packet << (sf::Uint32)entity->getID() << (sf::Uint8)entity->getType();
        entity->toPacket(packet);
    }
}

void World::fromPacket(sf::Packet& packet)
{
    sf::Uint16 new_size;
    sf::Uint32 id;
    sf::Uint8 type;

    packet >> new_size;
    for (auto entity_it = m_entityList.begin(); entity_it != m_entityList.end(); entity_it++) {
        packet >> id >> type;

        if (entity_it->get()->getID() == id) {
            entity_it->get()->fromPacket(packet);
        } else {
            m_entityList.erase(entity_it);
            m_entityList.emplace(entity_it, createEntity(this, static_cast<EntityType>(type), id));
            entity_it->get()->fromPacket(packet);
        }
    }

    if (new_size <= m_entityList.size()) {
        m_entityList.resize(new_size);
    } else {
        while (packet >> id >> type) {
            m_entityList.emplace_back(createEntity(this, static_cast<EntityType>(type), id));
            m_entityList.back()->fromPacket(packet);
        }
    }
}

std::vector<std::unique_ptr<Entity>>& World::getAllEntities() { return m_entityList; }

bool World::trySpawnSnake(unsigned int id)
{
    unsigned short int map_size = util::cfg::WINDOW_SIZE / util::cfg::CELL_SIZE;

    util::GridPos random_pos(
            rand() % (map_size - util::cfg::INITIAL_SNAKE_LENGHT) + util::cfg::INITIAL_SNAKE_LENGHT,
            rand() % (map_size - util::cfg::INITIAL_SNAKE_LENGHT) + util::cfg::INITIAL_SNAKE_LENGHT
    );

    for (auto& entity: m_entityList) {
        if (entity->isCellNearby(random_pos, util::cfg::INITIAL_SNAKE_LENGHT)) return false;
    }

    std::unique_ptr<Snake> snake = std::make_unique<Snake>(this, id, random_pos, static_cast<util::Direction>(rand() % 4), util::pickNextColor());
    m_entityList.push_back(std::move(snake));

    util::Logger(util::Priority::Info) << "Created snake " << id << " at " << (int) random_pos.col << "," << (int) random_pos.row << std::endl;
    return true;
}

Entity& World::getEntityById(unsigned int id)
{
    for (auto& entity: m_entityList) {
        if (entity->getID() == id) return *entity;
    }

    throw std::runtime_error("Entity " + std::to_string(id) + " is missing");
}

void World::removeEntityById(unsigned int id)
{
    bool found = false;

    for (auto entity_it = m_entityList.begin(); entity_it != m_entityList.end();) {
        if (entity_it->get()->getID() == id) {
            m_entityList.erase(entity_it);
            found = true;
        } else {
            entity_it++;
        }
    }

    if (!found) throw std::runtime_error("Cannot remove: Entity " + std::to_string(id) + " is missing");
    else util::Logger(util::Priority::Info) << "Removed entity " << id << std::endl;
}






