#include "NetworkClient.h"

#include "Network.h"

#include <SFML/Network.hpp>

#include <iostream>

void NetworkClient::setup(const sf::IpAddress &ip_address)
{
    if (m_socket.connect(ip_address, NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't connect to server");

    sf::Packet packet;

    packet << static_cast<sf::Uint8>(Request::Join);
    m_socket.send(packet);

    if (m_socket.receive(packet) != sf::Socket::Done)
        throw std::runtime_error("Connection lost");

    sf::Uint8 header;
    packet >> header;
    if (static_cast<Response>(header) != Response::JoinOk)
        throw std::runtime_error("Invalid server");

    std::cout << "Connected to " << ip_address << ":" << NETWORK_PORT << std::endl;
}
