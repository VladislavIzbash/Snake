#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/Packet.hpp>


/*
 *  Интерфейс объектов игры. Имеет идентификатор, функии рендера,
 *  обновления состояния(выполняется только на сервере)
 *  и сериализации в сетевые пакеты.
 */
class IObject {
public:
    virtual void draw(sf::RenderWindow& target) = 0;

    virtual void update() = 0;

    virtual sf::Packet& operator<<(sf::Packet& packet) = 0;
    virtual void operator>>(sf::Packet& packet) = 0;

    virtual void setID(unsigned int id) = 0;
    virtual unsigned int getID() = 0;
};

