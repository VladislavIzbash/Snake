#pragma once

#include "Network.h"

#include <SFML/Network/TcpSocket.hpp>


class NetworkClient: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;

    void initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list) override;

    void update(std::vector<std::unique_ptr<GameObject>>& object_list) override;

private:
    sf::TcpSocket m_socket;

    static void syncObjectList(std::vector<std::unique_ptr<GameObject>>& object_list, sf::Packet& packet);


};