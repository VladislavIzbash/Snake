#include "Snake.h"

#include "../Util.h"
#include "../Game/Game.h"

#include <iostream>


Snake::Snake(World* world_in, unsigned int id, util::GridPos head_pos, util::Direction dir, sf::Color snake_color):
    Entity(world_in, id), m_headPos(head_pos), m_direction(dir), m_color(snake_color)
{
    util::GridPos cur_pos(m_headPos);

    for (unsigned int i = 0; i < util::cfg::INITIAL_SNAKE_LENGHT; i++) {
        m_bodyVector.emplace_back(m_worldIn, 0, cur_pos, m_color);

        switch (m_direction) {
            case util::Direction::Right:
                cur_pos.col--;
                break;
            case util::Direction::Left:
                cur_pos.col++;
                break;
            case util::Direction::Up:
                cur_pos.row++;
                break;
            case util::Direction::Down:
                cur_pos.row--;
                break;
        }
    }

}

void Snake::update()
{
    sf::Uint8 map_size = util::cfg::WINDOW_SIZE / util::cfg::CELL_SIZE;

    switch (m_direction) {
        case util::Direction::Right:
            if (m_headPos.col++ == map_size) m_headPos.col = 0;
            break;
        case util::Direction::Left:
            if (m_headPos.col-- == 0) m_headPos.col = map_size;
            break;
        case util::Direction::Up:
            if (m_headPos.row-- == 0) m_headPos.row = map_size;
            break;
        case util::Direction::Down:
            if (m_headPos.row++ == map_size) m_headPos.row = 0;
            break;
    }

    Entity* ent = m_worldIn->getEntityAtPos(m_headPos);

    util::renderLock.lock();

    m_bodyVector.emplace(m_bodyVector.begin(), m_worldIn, 0, m_headPos, m_color);

    if (ent != nullptr && ent->getType() == EntityType::Fruit)
    {
        ent->setDead();
    } else {
        m_bodyVector.erase(m_bodyVector.end());
    }

    util::renderLock.unlock();
}

void Snake::toPacket(sf::Packet& packet)
{
    packet << (sf::Uint16)m_bodyVector.size() << (sf::Uint8)m_direction << m_color.toInteger();

    for (auto& part: m_bodyVector) {
        part.toPacket(packet);
    }
}

void Snake::fromPacket(sf::Packet& packet)
{
    sf::Uint16 new_size;
    sf::Uint8 dir;
    sf::Uint32 color;

    packet >> new_size >> dir >> color;

    util::renderLock.lock();
    m_color = sf::Color(color);
    m_bodyVector.resize(new_size, SnakeBodyPart(m_worldIn, 0, util::GridPos(), m_color));
    util::renderLock.unlock();

    for (auto& part: m_bodyVector) {
        part.fromPacket(packet);
        part.setColor(m_color);
    }

    util::renderLock.lock();
    m_headPos = m_bodyVector.begin()->getPos();
    m_direction = static_cast<util::Direction>(dir);
    util::renderLock.unlock();
}

EntityType Snake::getType() const { return EntityType::Snake; }

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& part: m_bodyVector) {
        util::renderLock.lock();
        target.draw(part);
        util::renderLock.unlock();
    }
}

void Snake::turn(util::Direction dir)
{
    m_direction = dir;
}

bool Snake::isCellNearby(util::GridPos cell_pos, unsigned int range) const
{
    for (auto& part: m_bodyVector) {
        if (part.isCellNearby(cell_pos, range)) return true;
    }

    return false;
}



