#include "Background.h"

#include <SFML/Graphics.hpp>


Background::Background(sf::Vector2f position, sf::Vector2u window_size, sf::Color color):
    GameObject(position)
{
    m_background_rect.setSize(sf::Vector2f(window_size));
    m_background_rect.setPosition(0, 0);
    m_background_rect.setFillColor(color);
}

sf::Drawable& Background::getDrawable()
{
    return m_background_rect;
}

sf::Packet& Background::operator<<(sf::Packet& packet)
{
    return packet;
}

void Background::operator>>(sf::Packet& packet) {}


