#pragma once

#include "../Core/GameObject.h"
#include "SnakeSegment.h"

#include <vector>
#include <SFML/Graphics/RenderTexture.hpp>

class Snake: public DynamicObject {
public:
    enum class Direction {
        RIGHT, LEFT, DOWN, UP
    };

    Snake(sf::Vector2f position, Direction direction, unsigned int lenght, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    void update() override;

    void operator>>(sf::Packet& packet) override;
    sf::Packet& operator<<(sf::Packet& packet) override;

private:
    std::vector<SnakeSegment> m_snake_body;
    unsigned int m_speed = 3;

};