#pragma once

#include "../Core/GameObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SnakeSegment: public GameObject {
public:
    static const unsigned int SEGMENT_SIZE = 50;

    explicit SnakeSegment(sf::Vector2f position, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    sf::Packet& operator<<(sf::Packet& packet) override;
    void operator>>(sf::Packet& packet) override;

private:
    sf::Texture* m_segment_texture;
    sf::Sprite m_segment_sprite;

};