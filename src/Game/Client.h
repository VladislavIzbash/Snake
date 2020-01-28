#pragma once

#include "Game.h"
#include "../World.h"

#include <SFML/Network/TcpSocket.hpp>


class Client: public IGame {
public:
    explicit Client(const std::string& address);

    void update() override;

    void render(sf::RenderTarget& target) override;

    Snake& getLocalPlayer() override;

private:
    World m_world;
    sf::TcpSocket m_socket;
    unsigned int m_myID = 0xffffffff;

};