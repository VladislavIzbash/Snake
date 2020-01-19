#include "Background.h"

#include <SFML/Graphics.hpp>


Background::Background(sf::Vector2f position, sf::Vector2u window_size, sf::Color color):
    GameObject(position)
{
    m_background_rect.setSize(sf::Vector2f(window_size));
    m_background_rect.setPosition(0, 0);
    m_background_rect.setFillColor(color);
}

void Background::draw(sf::RenderWindow& target)
{
    target.draw(m_background_rect);
}

sf::Packet& Background::operator<<(sf::Packet& packet)
{
    return packet;
}

void Background::operator>>(sf::Packet& packet) {}


