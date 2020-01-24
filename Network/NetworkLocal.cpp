#include "NetworkLocal.h"
#include "../GameObject.h"
#include "../Settings.h"
#include "../Snake/Snake.h"
#include "../Logger.h"
#include "../Game.h"

#include <cstdlib>


void NetworkLocal::setup(const sf::IpAddress &ip_address) {}

void NetworkLocal::initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    addNewPlayer(object_list, 0);
}

void NetworkLocal::addNewPlayer(std::vector<std::unique_ptr<GameObject>>& object_list, unsigned int id)
{
    unsigned short int map_size = settings::WINDOW_SIZE / settings::CELL_SIZE;

    GridPos random_pos = {
            .col = static_cast<unsigned char>(rand() % (map_size - settings::INITIAL_SNAKE_LENGHT) +
                                              settings::INITIAL_SNAKE_LENGHT),
            .row = static_cast<unsigned char>(rand() % (map_size - settings::INITIAL_SNAKE_LENGHT) +
                                              settings::INITIAL_SNAKE_LENGHT)
    };

    object_list.push_back(std::make_unique<Snake>(id, random_pos, Game::pickNextColor()));

    Logger(Priority::Info) << "Created Snake " << id << " at " << (int)random_pos.col << "," << (int)random_pos.row << std::endl;
}

void NetworkLocal::removePlayer(std::vector<std::unique_ptr<GameObject>>& object_list, unsigned int id)
{
    for (auto obj_it = object_list.begin(); obj_it != object_list.end();) {
        if (obj_it->get()->getID() == id) {
            object_list.erase(obj_it);
        } else {
            obj_it++;
        }
    }

    Logger(Priority::Info) << "Removed Snake " << id << std::endl;
}

void NetworkLocal::update(std::vector<std::unique_ptr<GameObject>>& object_list) {}

unsigned int NetworkLocal::getMyId() { return 0; }




