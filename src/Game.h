#pragma once

#include "Entity/Entity.h"
#include "Network/Network.h"
#include "Entity/Snake.h"

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>
#include <mutex>


extern std::mutex g_updateLock;

class Game {
public:
    explicit Game(INetwork& network);

    std::vector<std::unique_ptr<Entity>>& getEntities();

    void turnLocalPlayer(Direction dir);

    static sf::Color pickNextColor();

private:
    INetwork& m_network;
    std::vector<std::unique_ptr<Entity>> m_entityList;

    void mainLoop();

};
