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

    Snake(unsigned int id, GridPos grid_pos, Direction dir, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    sf::Packet& operator>>(sf::Packet& packet) override;
    bool operator<<(sf::Packet& packet) override;

    ObjectType getType() const override;

    void update() override;

    void turn(Direction dir);

private:
    std::vector<SnakeSegment> m_snake_body;
    Direction m_current_direction;
    sf::Color m_snake_color;

};