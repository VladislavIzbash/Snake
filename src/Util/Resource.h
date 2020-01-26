#pragma once

#include "../Entity/Entity.h"

#include <SFML/Graphics/Texture.hpp>


namespace res {
    void loadAll();

    sf::Texture* getTexture(EntityType type);

}