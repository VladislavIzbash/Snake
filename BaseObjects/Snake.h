#pragma once

#include "../Core/Object.h"
#include "SnakeSegment.h"

#include <vector>
#include <SFML/Graphics/RenderTexture.hpp>

class Snake: public IObject {
public:
    enum class Direction {
        RIGHT, LEFT, DOWN, UP
    };

    Snake(sf::Vector2f position, Direction direction, unsigned int initial_lenght, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    void operator>>(sf::Packet& packet) override;
    sf::Packet& operator<<(sf::Packet& packet) override;

private:
    std::vector<SnakeSegment> m_snake_body;
    unsigned int m_speed = 3;

};