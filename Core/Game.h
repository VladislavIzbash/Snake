#pragma once

#include "Network/Network.h"
#include "Object.h"

#include <map>


class Game {
public:
    explicit Game(INetwork& network);

private:
    static const int CELL_SIZE = 50;

    INetwork& m_network;
    std::vector<IObject> m_object_list;
};