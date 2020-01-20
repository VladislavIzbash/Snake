#pragma once

#include "../Core/Object.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

class SnakeSegment: public IObject {
public:
    explicit SnakeSegment(sf::Vector2f position, sf::Color snake_color);

    void draw(sf::RenderWindow& target) override;

    void update() override;

    sf::Packet& operator<<(sf::Packet& packet) override;
    void operator>>(sf::Packet& packet) override;

private:
    std::unique_ptr<sf::Texture> m_segment_texture;
    sf::Sprite m_segment_sprite;

};