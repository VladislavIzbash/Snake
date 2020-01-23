#pragma once

#include "../GameObject.h"
#include "SnakeSegment.h"

#include <vector>
#include <SFML/Graphics/RenderTexture.hpp>

class Snake: public GameObject {
public:
    enum class Direction {
        RIGHT, LEFT, DOWN, UP
    };

    Snake(unsigned int id, GridPos grid_pos, Direction direction, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    sf::Packet& operator>>(sf::Packet& packet) override;

    bool operator<<(sf::Packet& packet) override;

    ObjectType getType() const override;

private:
    std::vector<SnakeSegment> m_snake_body;

};