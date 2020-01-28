#pragma once

#include "../Entity/Entity.h"


enum class Request {
    Join, UpdateState
};
enum class Response {
    JoinOk, JoinFailure, UpdateOk
};

class INetwork {
public:
    virtual void initEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) = 0;

    virtual void updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) = 0;

    virtual Entity& getMyPlayer(const std::vector<std::unique_ptr<Entity>>& entity_list) = 0;

};