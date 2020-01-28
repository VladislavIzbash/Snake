#pragma once

#include "Entity.h"

#include "../Util.h"

#include <SFML/Graphics.hpp>


class SnakeBodyPart: public Entity {
public:
    SnakeBodyPart(World* world_in, unsigned int id, util::GridPos pos, sf::Color color = sf::Color::White);

    void toPacket(sf::Packet& packet) override;
    void fromPacket(sf::Packet& packet) override;

    EntityType getType() const override;

    void setColor(sf::Color color);
    util::GridPos getPos() const;

    bool isCellNearby(util::GridPos cell_pos, unsigned int range) const override;

private:
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};