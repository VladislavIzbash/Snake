#include "GameObject.h"
#include "Snake/SnakeSegment.h"
#include "Snake/Snake.h"

GameObject::GameObject(unsigned int id, GridPos grid_pos): m_id(id), m_grid_pos(grid_pos) {}

void GameObject::draw(sf::RenderWindow& target) {}

void GameObject::update() {}

sf::Packet& GameObject::operator>>(sf::Packet& packet) { return packet; }
bool GameObject::operator<<(sf::Packet& packet) { return true; }

ObjectType GameObject::getType() const { return ObjectType::None; }

unsigned int GameObject::getID() const { return m_id; }

std::unique_ptr<GameObject> createObject(ObjectType type, unsigned int id)
{
    switch (type) {
        case ObjectType::SnakeSegment:
            return std::make_unique<SnakeSegment>(id, GridPos(), sf::Color::Red);
        case ObjectType::Snake:
            return std::make_unique<Snake>(id, GridPos(), Snake::Direction::RIGHT, sf::Color::Red);
        default:
            throw std::runtime_error("Invalid type: " + std::to_string(static_cast<unsigned int>(type)));
    }
}
