#include "NetworkLocal.h"
#include "../GameObject.h"
#include "../Settings.h"
#include "../Snake/Snake.h"

#include <random>
#include <ctime>


void NetworkLocal::setup(const sf::IpAddress &ip_address) {}

void NetworkLocal::initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    unsigned short int map_size = settings::WINDOW_SIZE / settings::CELL_SIZE;
    std::default_random_engine rand((unsigned int)std::time(nullptr));

    std::uniform_int_distribution<unsigned char> pos_distrib(4, map_size - settings::INITIAL_SNAKE_LENGHT);

    GridPos random_pos = {pos_distrib(rand), pos_distrib(rand)};

    object_list.push_back(std::make_unique<Snake>(0, random_pos, Snake::Direction::RIGHT, sf::Color::Red));
}

void NetworkLocal::update(std::vector<std::unique_ptr<GameObject>>& object_list) {}
