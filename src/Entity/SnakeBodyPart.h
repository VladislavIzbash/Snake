#pragma once

#include "Entity.h"

#include "../Util/Grid.h"

#include <SFML/Graphics.hpp>


class SnakeBodyPart: public Entity {
public:
    SnakeBodyPart(unsigned int id, GridPos pos, sf::Color color = sf::Color::White);

    void toPacket(sf::Packet& packet) override;
    void fromPacket(sf::Packet& packet) override;

    EntityType getType() const override;

    void setColor(sf::Color color);
    GridPos getPos() const;

private:
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};