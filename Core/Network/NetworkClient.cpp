#include "NetworkClient.h"

#include <iostream>

void NetworkClient::setup(const sf::IpAddress &ip_address)
{
    if (m_socket.connect(ip_address, NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't connect to server");

    std::cout << "Connected to " << ip_address << ":" << NETWORK_PORT << std::endl;
}
