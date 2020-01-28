#pragma once

#include "../Entity/Snake.h"

#include <SFML/Graphics/RenderTarget.hpp>


enum class Request {
    Join, UpdateState
};
enum class Response {
    JoinOk, JoinFull, UpdateOk
};

enum class Direction;

class IGame {
public:
    virtual void update() = 0;

    virtual void render(sf::RenderTarget& target) = 0;

    virtual Snake& getLocalPlayer() = 0;

};
