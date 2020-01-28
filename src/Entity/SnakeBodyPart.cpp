#include "SnakeBodyPart.h"

#include "../Util.h"
#include "../Game/Game.h"


SnakeBodyPart::SnakeBodyPart(World* world_in, unsigned int id, util::GridPos pos, sf::Color color):
    Entity(world_in, id), m_sprite(*util::res::getTexture(EntityType::SnakeBodyPart))
{
    m_sprite.setPosition(pos.mapToWorld());
    m_sprite.setColor(color);
}



void SnakeBodyPart::toPacket(sf::Packet& packet)
{
    util::GridPos pos(m_sprite.getPosition());

    packet << (sf::Uint8)pos.col << (sf::Uint8)pos.row;
}

void SnakeBodyPart::fromPacket(sf::Packet& packet)
{
    util::GridPos pos;
    packet >> pos.col >> pos.row;

    util::renderLock.lock();
    m_sprite.setPosition(pos.mapToWorld());
    util::renderLock.unlock();
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

util::GridPos SnakeBodyPart::getPos() const
{
    return util::GridPos(m_sprite.getPosition());
}

bool SnakeBodyPart::isCellNearby(util::GridPos cell_pos, unsigned int range) const
{
    util::GridPos my_pos(m_sprite.getPosition());

    bool col_in_range = my_pos.col - range <= cell_pos.col && cell_pos.col <= my_pos.col + range;
    bool row_in_range = my_pos.row - range <= cell_pos.row && cell_pos.row <= my_pos.row + range;

    return col_in_range && row_in_range;
}
