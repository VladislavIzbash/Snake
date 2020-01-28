#include "Entity.h"

#include "Snake.h"
#include "../Util.h"

#include <stdexcept>


Entity::Entity(World* world_in, unsigned int id):
    m_worldIn(world_in), m_id(id) {}

void Entity::update() {}

void Entity::toPacket(sf::Packet& packet) {}
void Entity::fromPacket(sf::Packet& packet) {}

EntityType Entity::getType() const { return EntityType::None; }
unsigned int Entity::getID() const { return m_id; }

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

bool Entity::isCellNearby(util::GridPos cell_pos, unsigned int range) const { return false; }


std::unique_ptr<Entity> createEntity(World* world_in, EntityType type, unsigned int id)
{
    switch (type) {
        case EntityType::SnakeBodyPart:
            return std::make_unique<SnakeBodyPart>(world_in, id, util::GridPos());
        case EntityType::Snake:
            return std::make_unique<Snake>(world_in, id, util::GridPos());
        default:
            throw std::runtime_error("Invalid entity type");
    }
}
