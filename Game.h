#pragma once

#include "Network/Network.h"
#include "Object.h"

#include <vector>
#include <memory>

/*
 *  Игровая логика. Выполняется на сервере и клиенте, но управляет игрой только сервер.
 */
class Game {
public:
    struct GridPos {
        unsigned short int col;
        unsigned short int row;
    };

    explicit Game(INetwork& network);

    std::vector<std::unique_ptr<IObject>>& getObjects();

    static GridPos mapToGrid(sf::Vector2f pos);
    static sf::Vector2f mapToWorld(GridPos grid_pos);

private:
    INetwork& m_network;
    std::vector<std::unique_ptr<IObject>> m_object_list;

    void mainLoop();
};