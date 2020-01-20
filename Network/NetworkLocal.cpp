#include "NetworkLocal.h"
#include "../Object.h"
#include "../Game.h"
#include "../Settings.h"
#include "../Snake/Snake.h"

#include <random>
#include <ctime>


void NetworkLocal::setup(const sf::IpAddress &ip_address) {}

void NetworkLocal::initObjectList(std::vector<std::unique_ptr<IObject>>& object_list)
{
    unsigned short int map_size = settings::WINDOW_SIZE / settings::CELL_SIZE;
    std::default_random_engine rand((unsigned int)std::time(nullptr));

    std::uniform_int_distribution<unsigned short int> pos_distrib(4, map_size - settings::INITIAL_SNAKE_LENGHT);

    Game::GridPos random_pos = {pos_distrib(rand), pos_distrib(rand)};

    object_list.push_back(std::make_unique<Snake>(Game::mapToWorld(random_pos), Snake::Direction::RIGHT, sf::Color::Red));
    object_list.back()->setID(0); // ID Змеи сервера всегда 0
}
