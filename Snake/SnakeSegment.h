#pragma once

#include "../GameObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

class SnakeSegment: public GameObject {
public:
    SnakeSegment(unsigned int id, GridPos grid_pos, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    sf::Packet& operator>>(sf::Packet& packet) override;
    bool operator<<(sf::Packet& packet) override;

    ObjectType getType() const override;

    void setColor(sf::Color color);
private:
    std::unique_ptr<sf::Sprite> m_segment_sprite;

};