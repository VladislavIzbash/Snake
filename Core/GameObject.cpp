#include "GameObject.h"

GameObject::GameObject(sf::Vector2f position):
    m_position(position)
{}

sf::Vector2f GameObject::getPos()
{
    return m_position;
}

DynamicObject::DynamicObject(sf::Vector2f position) : GameObject(position) {}
