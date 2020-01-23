#include "SnakeSegment.h"
#include "../Settings.h"
#include "../Game.h"


SnakeSegment::SnakeSegment(unsigned int id, GridPos grid_pos, sf::Color snake_color): GameObject(id, grid_pos)
{
    sf::Image img;
    img.create(settings::CELL_SIZE, settings::CELL_SIZE, snake_color);

    m_segment_texture = std::make_unique<sf::Texture>();
    m_segment_texture->loadFromImage(img);

    m_segment_sprite.setTexture(*m_segment_texture);
    m_segment_sprite.setPosition(Game::mapToWorld(m_grid_pos));
}

void SnakeSegment::draw(sf::RenderWindow& target)
{
    target.draw(m_segment_sprite);
}

sf::Packet& SnakeSegment::operator>>(sf::Packet& packet)
{
    GridPos pos = Game::mapToGrid(m_segment_sprite.getPosition());
    packet << static_cast<sf::Uint8>(pos.col) << static_cast<sf::Uint8>(pos.row);

    return packet;
}

bool SnakeSegment::operator<<(sf::Packet& packet)
{
    GridPos pos = {0, 0};
    if (packet >> pos.col >> pos.row) {
        m_segment_sprite.setPosition(Game::mapToWorld(pos));
        return true;
    }
    return false;
}

ObjectType SnakeSegment::getType() const { return ObjectType::SnakeSegment; }

