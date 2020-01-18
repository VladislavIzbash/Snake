#include "NetworkServer.h"

#include <iostream>

void NetworkServer::setup(const sf::IpAddress &ip_address)
{
    if (m_listener.listen(NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't bind to port");

    std::cout << "Started server on 0.0.0.0:" << NETWORK_PORT << std::endl;
}
