#pragma once

#include "../Util.h"
#include "../World.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Network/Packet.hpp>

#include <memory>


enum class EntityType {
    None, SnakeBodyPart, Snake
};

class Entity: public sf::Drawable {
public:
    Entity(World* world_in, unsigned int id);

    virtual void update();

    virtual void toPacket(sf::Packet& packet);
    virtual void fromPacket(sf::Packet& packet);

    virtual EntityType getType() const;
    virtual unsigned int getID() const;

    virtual bool isCellNearby(util::GridPos cell_pos, unsigned int range) const;

protected:
    World* m_worldIn;
    unsigned int m_id;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


std::unique_ptr<Entity> createEntity(World* world_in, EntityType type, unsigned int id);
