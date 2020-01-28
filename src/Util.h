#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <ostream>
#include <mutex>


enum class EntityType;

namespace util {
    namespace cfg {
        const unsigned short int WINDOW_SIZE = 800;
        const unsigned short int CELL_SIZE = 25;
        const sf::Color BACKGROUND_COLOR(0, 230, 0);
        const unsigned short int NETWORK_PORT = 23402;
        const unsigned short int INITIAL_SNAKE_LENGHT = 7;
        const unsigned int SPAWN_ATTEMPTS = 5;
        const unsigned int UPDATE_INTERVAL_MS = 100;
        const unsigned int FRUIT_INTERVAL_MS = 500;
    }

    namespace res {
        void loadAll();

        sf::Texture* getTexture(EntityType type);
    }

    extern std::mutex renderLock;

    class GridPos {
    public:
        sf::Uint8 col;
        sf::Uint8 row;

        explicit GridPos(sf::Uint8 col = 0, sf::Uint8 row = 0);
        explicit GridPos(sf::Vector2f vector);

        sf::Vector2f mapToWorld();

    };

    enum class Direction {
        Right, Left, Up, Down
    };


    enum class Priority {
        Info, Warning, Error, Critical
    };

    class Logger {
    public:
        explicit Logger(Priority priority);

        std::ostream& operator <<(const std::string& msg);

    private:
        Priority m_priority;

    };

    sf::Color pickNextColor();

}