#include "Snake.h"
#include "../Settings.h"

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <iostream>

Snake::Snake(unsigned int id, GridPos grid_pos, Direction dir, sf::Color snake_color): GameObject(id, grid_pos), m_snake_color(snake_color)
{
    GridPos segment_pos(grid_pos);

    m_current_direction = dir;//static_cast<Direction>(rand() % 4);

    for (unsigned int i = 0; i < settings::INITIAL_SNAKE_LENGHT; ++i) {
        m_snake_body.emplace_back(NULL, segment_pos, snake_color);

        switch (m_current_direction) {
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
        segm.setColor(m_snake_color);
        segm.draw(target);
    }
}

sf::Packet& Snake::operator>>(sf::Packet& packet)
{
    packet << static_cast<sf::Uint16>(m_snake_body.size());
    packet << static_cast<sf::Uint8>(m_current_direction);
    packet << static_cast<sf::Uint8>(m_snake_color.r) << static_cast<sf::Uint8>(m_snake_color.g) << static_cast<sf::Uint8>(m_snake_color.b);

    for (SnakeSegment& segm: m_snake_body) {
        segm >> packet;
    }

    return packet;
}

bool Snake::operator<<(sf::Packet& packet)
{
    unsigned short int new_size;
    sf::Uint8 dir;

    packet >> new_size >> dir;
    packet >> m_snake_color.r >> m_snake_color.g >> m_snake_color.b;

    if (m_snake_body.size() <= new_size) {
        for (SnakeSegment& segm: m_snake_body) {
            segm << packet;
        }
        for (unsigned int i = 0; i < new_size - m_snake_body.size(); ++i) {
            m_snake_body.emplace_back(0, GridPos(), sf::Color::Red);
            m_snake_body.back() << packet;
        }
    } else {
        m_snake_body.erase(m_snake_body.end() + 1, m_snake_body.end() + m_snake_body.size() - new_size);
        for (SnakeSegment& segm: m_snake_body) {
            segm << packet;
        }
    }

    m_current_direction = static_cast<Direction>(dir);

    //std::cout << std::endl;
    return m_snake_body.size() == new_size;
}

ObjectType Snake::getType() const { return ObjectType::Snake; }

void Snake::turn(Direction dir)
{
    /*switch (m_current_direction) {
        case Direction::RIGHT:
            head_pos.col++;
            break;
        case Direction::LEFT:
            head_pos.col--;
            break;
        case Direction::DOWN:
            head_pos.row++;
            break;
        case Direction::UP:
            head_pos.row--;
            break;
    }*/

    m_current_direction = dir;
}

void Snake::update()
{
    unsigned char map_size = settings::WINDOW_SIZE / settings::CELL_SIZE;

    GridPos head_pos = m_snake_body.begin()->getPos();

    switch (m_current_direction) {
        case Direction::RIGHT:
           if (head_pos.col++ >= map_size) head_pos.col = 0;
           break;
        case Direction::LEFT:
            if (head_pos.col-- <= 0) head_pos.col = map_size;
            break;
        case Direction::DOWN:
            if (head_pos.row++ >= map_size) head_pos.row = 0;
            break;
        case Direction::UP:
            if (head_pos.row-- <= 0) head_pos.row = map_size;
            break;
    }

    m_snake_body.emplace(m_snake_body.begin(), 0, head_pos, m_snake_color);
    m_snake_body.erase(m_snake_body.end());
}



