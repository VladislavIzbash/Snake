#pragma once

#include "INetwork.h"

#include <SFML/Network/TcpSocket.hpp>


class NetworkClient: public INetwork {
public:
    void setup(const sf::IpAddress &ip_address) override;

private:
    sf::TcpSocket m_socket;
};