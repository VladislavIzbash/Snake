#include "Fruit.h"

#include "../Util.h"

#include <SFML/Graphics/RenderTarget.hpp>


Fruit::Fruit(World* world_in, unsigned int id, util::GridPos pos):
    Entity(world_in, id), m_sprite(*util::res::getTexture(EntityType::Fruit))
{
    m_sprite.setPosition(pos.mapToWorld());
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}

bool Fruit::isCellNearby(util::GridPos cell_pos, unsigned int range) const
{
    util::GridPos my_pos(m_sprite.getPosition());

    bool col_in_range = my_pos.col - range <= cell_pos.col && cell_pos.col <= my_pos.col + range;
    bool row_in_range = my_pos.row - range <= cell_pos.row && cell_pos.row <= my_pos.row + range;

    return col_in_range && row_in_range;
}

EntityType Fruit::getType() const { return EntityType::Fruit; }

void Fruit::toPacket(sf::Packet& packet)
{
    util::GridPos pos(m_sprite.getPosition());

    packet << pos.col << pos.row;
}

void Fruit::fromPacket(sf::Packet& packet)
{
    util::GridPos pos;
    packet >> pos.col >> pos.row;

    util::renderLock.lock();
    m_sprite.setPosition(pos.mapToWorld());
    util::renderLock.unlock();
}
