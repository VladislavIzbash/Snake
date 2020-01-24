#pragma once

#include "NetworkLocal.h"

#include <SFML/Network/TcpListener.hpp>

#include <vector>
#include <memory>


class NetworkServer: public NetworkLocal {
public:
    void setup(const sf::IpAddress &ip_address) override;

    void update(std::vector<std::unique_ptr<GameObject>>& object_list) override;

private:
    struct Client {
        std::shared_ptr<sf::TcpSocket> socket;
        unsigned int id;
    };

    sf::TcpListener m_listener;
    std::vector<Client> m_client_list;

    void handleNewConnections(std::vector<std::unique_ptr<GameObject>>& object_list);

    static sf::Packet buildUpdatePacket(std::vector<std::unique_ptr<GameObject>>& object_list);

};
