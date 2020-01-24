#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Network/Network.h"


/*
 *  Игровая логика. Выполняется на сервере и клиенте, но управляет игрой только сервер.
 */
class Game {
public:
    explicit Game(INetwork& network);

    std::vector<std::unique_ptr<GameObject>>& getObjects();

    static GridPos mapToGrid(sf::Vector2f pos);
    static sf::Vector2f mapToWorld(GridPos grid_pos);

    static sf::Color pickNextColor();

private:
    INetwork& m_network;
    std::vector<std::unique_ptr<GameObject>> m_object_list;

    void mainLoop();

};
