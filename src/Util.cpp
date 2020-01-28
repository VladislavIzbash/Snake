#include "Util.h"

#include "Entity/Entity.h"

#include <iostream>


static sf::Texture* g_snakePartTexture = nullptr;
static sf::Texture* g_fruitTexture = nullptr;

void util::res::loadAll()
{
    sf::Image img;
    img.create(cfg::CELL_SIZE, cfg::CELL_SIZE, sf::Color::White);

    g_snakePartTexture = new sf::Texture();
    g_snakePartTexture->loadFromImage(img);

    img.create(cfg::CELL_SIZE, cfg::CELL_SIZE, sf::Color::Magenta);
    g_fruitTexture = new sf::Texture();
    g_fruitTexture->loadFromImage(img);
}

sf::Texture* util::res::getTexture(EntityType type)
{
    switch (type) {
        case EntityType::SnakeBodyPart:
            return g_snakePartTexture;
        case EntityType::Fruit:
            return g_fruitTexture;
        default:
            throw std::runtime_error("No texture for that entity");
    }
}


std::mutex util::renderLock;


util::GridPos::GridPos(sf::Uint8 col, sf::Uint8 row):
    col(col), row(row) {}

util::GridPos::GridPos(sf::Vector2f vector):
    col(vector.x / cfg::CELL_SIZE), row(vector.y / cfg::CELL_SIZE) {}

sf::Vector2f util::GridPos::mapToWorld()
{
    return sf::Vector2f(col * cfg::CELL_SIZE, row * cfg::CELL_SIZE);
}

util::GridPos util::getRandomPos()
{
    sf::Uint8 map_size = cfg::WINDOW_SIZE / cfg::CELL_SIZE;

    return GridPos(rand() % map_size, rand() % map_size);
}


util::Logger::Logger(util::Priority priority): m_priority(priority) {}

std::ostream& util::Logger::operator<<(const std::string& msg)
{
    switch (m_priority) {
        case Priority::Info:
            std::cout << "INFO: " << msg;
            return std::cout;
        case Priority::Warning:
            std::cerr << "WARN: " << msg;
            break;
        case Priority::Error:
            std::cerr << "ERROR: " << msg;
            break;
        case Priority::Critical:
            std::cerr << "FATAL: " << msg;
            break;
    }
    return std::cerr;
}

sf::Color util::pickNextColor()
{
    static unsigned int m_counter = 0;
    const std::vector<sf::Color> color_pool {
            sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Black, sf::Color::Yellow
    };

    return color_pool.at( m_counter++ % color_pool.size());
}





