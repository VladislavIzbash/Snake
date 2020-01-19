#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(sf::Vector2f position, sf::Color snake_color):
    GameObject(position), m_segment_texture(new sf::Texture())
{
    sf::Image img;
    img.create(SEGMENT_SIZE, SEGMENT_SIZE, snake_color);
    m_segment_texture->loadFromImage(img);

    m_segment_sprite.setTexture(*m_segment_texture);
    m_segment_sprite.setPosition(m_position);
}

void SnakeSegment::draw(sf::RenderWindow& target)
{
    target.draw(m_segment_sprite);
}

sf::Packet& SnakeSegment::operator<<(sf::Packet& packet)
{
    return packet;
}

void SnakeSegment::operator>>(sf::Packet& packet)
{
}


