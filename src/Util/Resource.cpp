#include "Resource.h"
#include "Config.h"

#include <stdexcept>


static sf::Texture* g_snakePartTexture = nullptr;

void res::loadAll()
{
    sf::Image img;
    img.create(cfg::CELL_SIZE, cfg::CELL_SIZE, sf::Color::White);

    g_snakePartTexture = new sf::Texture();
    g_snakePartTexture->loadFromImage(img);
}

sf::Texture* res::getTexture(EntityType type)
{
    switch (type) {
        case EntityType::SnakeBodyPart:
            return g_snakePartTexture;
        default:
            throw std::runtime_error("No texture for that object");
    }
}
