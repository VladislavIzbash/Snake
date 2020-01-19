#include "Snake.h"

#include <SFML/Graphics.hpp>


Snake::Snake(sf::Vector2f position, Snake::Direction direction, unsigned int lenght, sf::Color snake_color):
    DynamicObject(position)
{
    sf::Vector2f local_pos(position);
    for (unsigned int i = 0; i < lenght; ++i) {
        m_snake_body.emplace_back(local_pos, snake_color);

        switch (direction) {
            case Direction::RIGHT:
                local_pos.x -= SnakeSegment::SEGMENT_SIZE;
                break;
            case Direction::LEFT:
                local_pos.x += SnakeSegment::SEGMENT_SIZE;
                break;
            case Direction::DOWN:
                local_pos.y -= SnakeSegment::SEGMENT_SIZE;
                break;
            case Direction::UP:
                local_pos.y += SnakeSegment::SEGMENT_SIZE;
                break;
        }
    }
}

void Snake::draw(sf::RenderWindow& target)
{
    for (SnakeSegment& segm: m_snake_body)
        segm.draw(target);
}

sf::Packet& Snake::operator<<(sf::Packet& packet)
{
    return packet;
}

void Snake::operator>>(sf::Packet& packet)
{
}

void Snake::update()
{
}

