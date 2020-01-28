#pragma once

#include <SFML/Graphics/Color.hpp>


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
