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
    sf::TcpListener m_listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> m_client_list;

    void acceptLoopThread();

    static sf::Packet buildUpdatePacket(std::vector<std::unique_ptr<GameObject>>& object_list);


};
