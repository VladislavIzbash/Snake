#include "Entity.h"

#include "Snake.h"

#include <stdexcept>


Entity::Entity(unsigned int id): m_id(id) {}

void Entity::update() {}

void Entity::toPacket(sf::Packet& packet) {}
void Entity::fromPacket(sf::Packet& packet) {}

EntityType Entity::getType() const { return EntityType::None; }
unsigned int Entity::getID() const { return m_id; }

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {}


std::unique_ptr<Entity> createEntity(EntityType type, unsigned int id)
{
    switch (type) {
        case EntityType::SnakeBodyPart:
            return std::make_unique<SnakeBodyPart>(id, GridPos());
        case EntityType::Snake:
            return std::make_unique<Snake>(id, GridPos());
        default:
            throw std::runtime_error("Invalid entity type");
    }
}
