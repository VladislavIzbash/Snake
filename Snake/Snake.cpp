#include "Snake.h"
#include "../Settings.h"

#include <SFML/Graphics.hpp>


Snake::Snake(unsigned int id, GridPos grid_pos, Direction direction, sf::Color snake_color): GameObject(id, grid_pos)
{
    GridPos segment_pos(grid_pos);

    for (unsigned int i = 0; i < settings::INITIAL_SNAKE_LENGHT; ++i) {
        m_snake_body.emplace_back(NULL, segment_pos, snake_color);

        switch (direction) {
            case Direction::RIGHT:
                --segment_pos.col;
                break;
            case Direction::LEFT:
                ++segment_pos.col;
                break;
            case Direction::DOWN:
                --segment_pos.row;
                break;
            case Direction::UP:
                ++segment_pos.row;
                break;
        }
    }
}

void Snake::draw(sf::RenderWindow& target)
{
    for (SnakeSegment& segm: m_snake_body) {
        segm.draw(target);
    }
}

sf::Packet& Snake::operator>>(sf::Packet& packet)
{
    packet << static_cast<sf::Uint16>(m_snake_body.size());

    for (SnakeSegment& segm: m_snake_body) {
        segm >> packet;
    }

    return packet;
}

bool Snake::operator<<(sf::Packet& packet)
{
    unsigned short int size;
    packet >> size;
    m_snake_body.clear();

    for (int i = 0; i < size; ++i) {
        m_snake_body.emplace_back(0, GridPos(), sf::Color::Red);
        m_snake_body.back() << packet;
    }

    return m_snake_body.size() == size;
}

ObjectType Snake::getType() const { return ObjectType::Snake; }



