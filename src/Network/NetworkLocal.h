#pragma once

#include "Network.h"

#include <memory>


class NetworkLocal: public INetwork {
public:
    void initEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) override;

    void updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) override;

    Entity& getMyPlayer(const std::vector<std::unique_ptr<Entity>>& entity_list) override;

protected:
    static bool spawnPlayer(std::vector<std::unique_ptr<Entity>>& entity_list, unsigned int id);
    static void removePlayer(std::vector<std::unique_ptr<Entity>>& entity_list, unsigned int id);

private:
    static bool tryRandomPosition(std::vector<std::unique_ptr<Entity>>& entity_list);

};
