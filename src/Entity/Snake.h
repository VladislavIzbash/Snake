#pragma once

#include "Entity.h"
#include "SnakeBodyPart.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include <vector>


class Snake: public Entity {
public:
    Snake(World* world_in, unsigned int id, util::GridPos head_pos, util::Direction dir = util::Direction::Right, sf::Color snake_color = sf::Color::White);

    void update() override;

    void toPacket(sf::Packet& packet) override;
    void fromPacket(sf::Packet& packet) override;

    EntityType getType() const override;

    bool isCellNearby(util::GridPos cell_pos, unsigned int range) const override;

    void turn(util::Direction dir);

private:
    std::vector<SnakeBodyPart> m_bodyVector;
    util::GridPos m_headPos;
    util::Direction m_direction;
    sf::Color m_color;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};