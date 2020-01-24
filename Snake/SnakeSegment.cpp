#include "SnakeSegment.h"

#include "../Game.h"

#include "../Settings.h"
#include "../Resources.h"


SnakeSegment::SnakeSegment(unsigned int id, GridPos grid_pos, sf::Color snake_color): GameObject(id, grid_pos)
{
    m_segment_sprite = std::make_unique<sf::Sprite>(*Resource::getTexture(ObjectType::SnakeSegment));
    m_segment_sprite->setPosition(Game::mapToWorld(m_grid_pos));
    m_segment_sprite->setColor(snake_color);
}

void SnakeSegment::draw(sf::RenderWindow& target)
{
    target.draw(*m_segment_sprite);
}

sf::Packet& SnakeSegment::operator>>(sf::Packet& packet)
{
    GridPos pos = Game::mapToGrid(m_segment_sprite->getPosition());
    packet << static_cast<sf::Uint8>(pos.col) << static_cast<sf::Uint8>(pos.row);

    return packet;
}

bool SnakeSegment::operator<<(sf::Packet& packet)
{
    GridPos pos = {0, 0};
    if (packet >> pos.col >> pos.row) {
        m_segment_sprite->setPosition(Game::mapToWorld(pos));
        return true;
    }
    return false;
}

ObjectType SnakeSegment::getType() const { return ObjectType::SnakeSegment; }

void SnakeSegment::setColor(sf::Color color)
{
    m_segment_sprite->setColor(color);
}

