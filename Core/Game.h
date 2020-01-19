#pragma once

#include "Network/Network.h"


class Game {
public:
    explicit Game(INetwork& network);

private:
    static const int CELL_SIZE = 50;

    INetwork& m_network;
};