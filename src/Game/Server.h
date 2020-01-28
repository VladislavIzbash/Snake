#pragma once

#include "Singleplayer.h"

#include <SFML/Network/TcpListener.hpp>


class Server: public Singleplayer {
public:
    Server();

    void update() override;

private:
    struct Client {
        std::shared_ptr<sf::TcpSocket> socket;
        unsigned int id;
    };

    sf::TcpListener m_listener;
    std::vector<Client> m_clientList;

    void handleNewConnections();
    bool handleUpdateRequest(Client& client);

};