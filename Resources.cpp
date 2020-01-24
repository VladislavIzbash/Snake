#include "Resources.h"
#include "Settings.h"


sf::Texture* snake_segment_texture;

void Resource::loadAll()
{
    sf::Image img;
    img.create(settings::CELL_SIZE, settings::CELL_SIZE, sf::Color::White);
    snake_segment_texture = new sf::Texture();
    snake_segment_texture->loadFromImage(img);
}

sf::Texture* Resource::getTexture(ObjectType type)
{
    switch (type) {
        case ObjectType::SnakeSegment:
            return snake_segment_texture;
        default:
            throw std::runtime_error("No texture for that object");
    }
}
