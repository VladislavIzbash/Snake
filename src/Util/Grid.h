#pragma once

#include <SFML/System/Vector2.hpp>


enum class Direction;

struct GridPos {
    unsigned char col = 0;
    unsigned char row = 0;

    void move(Direction dir, int range);
};

GridPos operator +(GridPos& a, GridPos& b);
GridPos operator -(GridPos& a, GridPos& b);


GridPos mapToGrid(sf::Vector2f pos);
sf::Vector2f mapToWorld(GridPos grid_pos);
