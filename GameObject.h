#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/Packet.hpp>


struct GridPos {
    unsigned char col = 0;
    unsigned char row = 0;
};

enum class ObjectType {
    None, Snake, SnakeSegment
};


/*
 *  Базовый класс объектов игры. Имеет идентификатор, функии рендера,
 *  обновления состояния(выполняется только на сервере)
 *  и сериализации в сетевые пакеты.
 */
class GameObject {
public:
    GameObject(unsigned int id, GridPos grid_pos);

    virtual void draw(sf::RenderWindow& target);

    virtual void update();

    virtual sf::Packet& operator>>(sf::Packet& packet);
    virtual bool operator<<(sf::Packet& packet);

    virtual ObjectType getType() const;
    virtual unsigned int getID() const;

protected:
    unsigned int m_id;
    GridPos m_grid_pos;

};

std::unique_ptr<GameObject> createObject(ObjectType type, unsigned int id);
