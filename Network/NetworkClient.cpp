#include "NetworkClient.h"

#include "Network.h"
#include "../Logger.h"
#include "../Settings.h"

#include <SFML/Network.hpp>


void NetworkClient::setup(const sf::IpAddress &ip_address)
{
    sf::Packet packet;
    sf::Uint8 header = 0;

    if (m_socket.connect(ip_address, settings::NETWORK_PORT) != sf::Socket::Done) {
        throw std::runtime_error("Couldn't connect to server");
    }

    packet << static_cast<sf::Uint8>(Request::Join);
    m_socket.send(packet);

    if (m_socket.receive(packet) != sf::Socket::Done) {
        throw std::runtime_error("Connection lost");
    }

    packet >> header;
    if (header != static_cast<sf::Uint8>(Response::JoinOk)) {
        throw std::runtime_error("Server refused join");
    }

    Logger(Priority::Info) << "Connected to " << ip_address << ":" << settings::NETWORK_PORT << std::endl;
}
