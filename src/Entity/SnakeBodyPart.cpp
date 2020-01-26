#include "SnakeBodyPart.h"

#include "../Util/Resource.h"


SnakeBodyPart::SnakeBodyPart(unsigned int id, GridPos pos, sf::Color color):
    Entity(id), m_sprite(*res::getTexture(EntityType::SnakeBodyPart))
{
    m_sprite.setPosition(mapToWorld(pos));
    m_sprite.setColor(color);
}



void SnakeBodyPart::toPacket(sf::Packet& packet)
{
    GridPos pos = mapToGrid(m_sprite.getPosition());

    packet << (sf::Uint8)pos.col << (sf::Uint8)pos.row;
}

void SnakeBodyPart::fromPacket(sf::Packet& packet)
{
    GridPos pos;
    packet >> pos.col >> pos.row;

    m_sprite.setPosition(mapToWorld(pos));
}

void SnakeBodyPart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

EntityType SnakeBodyPart::getType() const { return EntityType::SnakeBodyPart; }

void SnakeBodyPart::setColor(sf::Color color)
{
    m_sprite.setColor(color);
}

GridPos SnakeBodyPart::getPos() const
{
    return mapToGrid(m_sprite.getPosition());
}
