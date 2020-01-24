#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "GameObject.h"


class Resource {
public:
    static void loadAll();

    static sf::Texture* getTexture(ObjectType type);

};