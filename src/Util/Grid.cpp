#include "Grid.h"

#include "../Entity/Snake.h"

#include "Config.h"


GridPos operator+(GridPos& a, GridPos& b)
{
    return {static_cast<unsigned char>(a.col + b.col), static_cast<unsigned char>(a.row + b.row)};
}
GridPos operator-(GridPos& a, GridPos& b)
{
    return {static_cast<unsigned char>(a.col - b.col), static_cast<unsigned char>(a.row - b.row)};
}


GridPos mapToGrid(sf::Vector2f pos)
{
    return {static_cast<unsigned char>(pos.x / cfg::CELL_SIZE), static_cast<unsigned char>(pos.y / cfg::CELL_SIZE)};
}

sf::Vector2f mapToWorld(GridPos grid_pos)
{
    return sf::Vector2f(grid_pos.col * cfg::CELL_SIZE, grid_pos.row * cfg::CELL_SIZE);
}


void GridPos::move(Direction dir, int range)
{
    unsigned short int map_size = cfg::WINDOW_SIZE / cfg::CELL_SIZE;

    switch (dir) {
        case Direction::RIGHT:
            if (col == map_size - 1) col = 0;
            else col += range;
            break;
        case Direction::LEFT:
            if (col == 0) col = map_size - 1;
            else col -= range;
            break;
        case Direction::DOWN:
            if (row == map_size - 1) row = 0;
            else row += range;
            break;
        case Direction::UP:
            if (row == 0) row = map_size - 1;
            else row -= range;
            break;
    }
}


