#include "SnakeBodyPart.h"

#include "../Util/Resource.h"
#include "../Game.h"


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

    g_updateLock.lock();
    m_sprite.setPosition(mapToWorld(pos));
    g_updateLock.unlock();
}

void SnakeBodyPart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    g_updateLock.lock();
    target.draw(m_sprite);
    g_updateLock.unlock();
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

bool SnakeBodyPart::isCellNearby(GridPos cell_pos, unsigned int range) const
{
    GridPos my_pos = mapToGrid(m_sprite.getPosition());

    bool col_in_range = my_pos.col - range <= cell_pos.col && cell_pos.col <= my_pos.col + range;
    bool row_in_range = my_pos.row - range <= cell_pos.row && cell_pos.row <= my_pos.row + range;

    return col_in_range && row_in_range;
}
