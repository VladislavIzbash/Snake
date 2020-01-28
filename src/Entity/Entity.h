#pragma once

#include "../Util/Grid.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Network/Packet.hpp>

#include <memory>
#include <mutex>


enum class EntityType {
    None, SnakeBodyPart, Snake
};

class Entity: public sf::Drawable {
public:
    explicit Entity(unsigned int id);

    virtual void update();

    virtual void toPacket(sf::Packet& packet);
    virtual void fromPacket(sf::Packet& packet);

    virtual EntityType getType() const;
    virtual unsigned int getID() const;

    virtual bool isCellNearby(GridPos cell_pos, unsigned int range) const;

protected:
    unsigned int m_id;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


std::unique_ptr<Entity> createEntity(EntityType type, unsigned int id);
