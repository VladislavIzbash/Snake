#pragma once

#include "NetworkLocal.h"

#include <SFML/Network/TcpListener.hpp>

class NetworkServer: public NetworkLocal {
public:
    void setup(const sf::IpAddress &ip_address) override;

private:
    sf::TcpListener m_listener;
};
