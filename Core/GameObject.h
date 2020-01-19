#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/Packet.hpp>

class GameObject {
public:
    explicit GameObject(sf::Vector2f position);

    virtual sf::Vector2f getPos();

    virtual sf::Drawable& getDrawable() = 0;

    virtual sf::Packet& operator<<(sf::Packet& packet) = 0;
    virtual void operator>>(sf::Packet& packet) = 0;

protected:
    sf::Vector2f m_position;
};

