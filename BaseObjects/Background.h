#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "../Core/GameObject.h"

class Background: public GameObject {
public:
    Background(sf::Vector2f position, sf::Vector2u window_size, sf::Color color);

    sf::Drawable& getDrawable() override;

    sf::Packet& operator<<(sf::Packet& packet) override;
    void operator>>(sf::Packet& packet) override;

private:
    sf::RectangleShape m_background_rect;

};