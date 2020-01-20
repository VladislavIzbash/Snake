#include "SnakeSegment.h"
#include "../Settings.h"

SnakeSegment::SnakeSegment(sf::Vector2f position, sf::Color snake_color)
{
    sf::Image img;
    img.create(settings::CELL_SIZE, settings::CELL_SIZE, snake_color);

    m_segment_texture = std::make_unique<sf::Texture>();
    m_segment_texture->loadFromImage(img);

    m_segment_sprite.setTexture(*m_segment_texture);
    m_segment_sprite.setPosition(position);
}

void SnakeSegment::draw(sf::RenderWindow& target)
{
    target.draw(m_segment_sprite);
}

sf::Packet& SnakeSegment::operator<<(sf::Packet& packet) { return packet; }

void SnakeSegment::operator>>(sf::Packet& packet) {}

void SnakeSegment::update() {}


