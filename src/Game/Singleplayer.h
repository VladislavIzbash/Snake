#pragma once

#include "Game.h"
#include "../World.h"

class Singleplayer: public IGame {
public:
    Singleplayer();

    void update() override;

    void render(sf::RenderTarget& target) override;

    Snake& getLocalPlayer() override;

protected:
    World m_world;

};