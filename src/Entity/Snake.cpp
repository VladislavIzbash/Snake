#include "Snake.h"

#include "../Util/Config.h"
#include "../Game.h"

#include <SFML/Graphics.hpp>


Snake::Snake(unsigned int id, GridPos head_pos, Direction dir, sf::Color snake_color):
    Entity(id), m_headPos(head_pos), m_direction(dir), m_color(snake_color)
{
    GridPos cur_pos = m_headPos;

    for (unsigned int i = 0; i < cfg::INITIAL_SNAKE_LENGHT; i++) {
        m_bodyVector.emplace_back(0, cur_pos, m_color);

        cur_pos.move(m_direction, -1);
    }

}

void Snake::update()
{
    m_headPos.move(m_direction, 1);

    m_bodyVector.emplace(m_bodyVector.begin(), 0, m_headPos, m_color);
    m_bodyVector.erase(m_bodyVector.end());
}

void Snake::toPacket(sf::Packet& packet)
{
    packet << (sf::Uint16)m_bodyVector.size() << (sf::Uint8)m_direction;
    packet << (sf::Uint8)m_color.r << (sf::Uint8)m_color.g << (sf::Uint8)m_color.b;

    for (auto& part: m_bodyVector) {
        part.toPacket(packet);
    }
}

void Snake::fromPacket(sf::Packet& packet)
{
;

    sf::Uint16 new_size;
    sf::Uint8 dir;

    packet >> new_size >> dir;
    packet >> m_color.r >> m_color.g >> m_color.b;

    g_updateLock.lock();
    m_bodyVector.resize(new_size, SnakeBodyPart(0, GridPos(), m_color));
    g_updateLock.unlock();

    for (auto& part: m_bodyVector) {
        part.fromPacket(packet);
        part.setColor(m_color);
    }

    g_updateLock.lock();
    m_headPos = m_bodyVector.begin()->getPos();
    m_direction = static_cast<Direction>(dir);
    g_updateLock.unlock();
}

EntityType Snake::getType() const { return EntityType::Snake; }

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& part: m_bodyVector) {
        target.draw(part);
    }
}

void Snake::turn(Direction dir)
{
    m_direction = dir;
}

bool Snake::isCellNearby(GridPos cell_pos, unsigned int range) const
{
    for (auto& part: m_bodyVector) {
        if (part.isCellNearby(cell_pos, range)) return true;
    }

    return false;
}



