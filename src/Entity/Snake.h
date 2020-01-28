#pragma once

#include "Entity.h"
#include "SnakeBodyPart.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include <vector>
#include <mutex>


enum class Direction {
    RIGHT, LEFT, DOWN, UP
};

class Snake: public Entity {
public:
    Snake(unsigned int id, GridPos head_pos, Direction dir = Direction::RIGHT, sf::Color snake_color = sf::Color::White);

    void update() override;

    void toPacket(sf::Packet& packet) override;
    void fromPacket(sf::Packet& packet) override;

    EntityType getType() const override;

    bool isCellNearby(GridPos cell_pos, unsigned int range) const override;

    void turn(Direction dir);

private:
    std::vector<SnakeBodyPart> m_bodyVector;
    GridPos m_headPos;
    Direction m_direction;
    sf::Color m_color;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};