#include "NetworkLocal.h"

#include "../Util/Config.h"
#include "../Util/Grid.h"
#include "../Util/Logger.h"
#include "../Entity/Snake.h"
#include "../Game.h"

#include <cstdlib>



void NetworkLocal::initEntityList(std::vector<std::unique_ptr<Entity>>& entity_list)
{
    addNewPlayer(entity_list, 0);
}

void NetworkLocal::updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) {}

Entity& NetworkLocal::getMyPlayer(const std::vector<std::unique_ptr<Entity>>& entity_list)
{
    for (auto& entity: entity_list) {
        if (entity->getID() == 0) return *entity;
    }

    throw std::runtime_error("My player is missing!");
}


void NetworkLocal::addNewPlayer(std::vector<std::unique_ptr<Entity>>& entity_list, unsigned int id)
{
    unsigned short int map_size = cfg::WINDOW_SIZE / cfg::CELL_SIZE;

    GridPos random_pos = {
            static_cast<unsigned char>(rand() % (map_size - cfg::INITIAL_SNAKE_LENGHT) + cfg::INITIAL_SNAKE_LENGHT),
            static_cast<unsigned char>(rand() % (map_size - cfg::INITIAL_SNAKE_LENGHT) + cfg::INITIAL_SNAKE_LENGHT)
    };

    entity_list.push_back(std::make_unique<Snake>(id, random_pos, static_cast<Direction>(rand() % 4), Game::pickNextColor()));

    Logger(Priority::Info) << "Created snake " << id << " at " << (int)random_pos.col << "," << (int)random_pos.row << std::endl;
}

void NetworkLocal::removePlayer(std::vector<std::unique_ptr<Entity>>& object_list, unsigned int id)
{
    for (auto entity_it = object_list.begin(); entity_it != object_list.end();) {
        if (entity_it->get()->getID() == id) {
            object_list.erase(entity_it);
        } else {
            entity_it++;
        }
    }

    Logger(Priority::Info) << "Removed snake " << id << std::endl;
}





