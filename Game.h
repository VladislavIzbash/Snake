#pragma once

#include "Network.h"


class Game {
public:
    explicit Game(Network& network);

private:
    static const int CELL_SIZE = 50;

    Network& m_network;
};