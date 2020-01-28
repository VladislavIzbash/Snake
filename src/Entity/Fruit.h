#pragma once

#include "Entity.h"

#include <SFML/Graphics/Sprite.hpp>


class Fruit: public Entity {
public:
    Fruit(World* world_in, unsigned int id, util::GridPos pos);

    void toPacket(sf::Packet& packet) override;

    void fromPacket(sf::Packet& packet) override;

    bool isCellNearby(util::GridPos cell_pos, unsigned int range) const override;

    EntityType getType() const override;

private:
    sf::Sprite m_sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
