#include "NetworkServer.h"

#include "Network.h"

#include <SFML/Network.hpp>

#include <iostream>
#include <thread>

void NetworkServer::setup(const sf::IpAddress &ip_address)
{
    if (m_listener.listen(NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't bind to port");

    (new std::thread(&NetworkServer::acceptLoopThread, this))->detach();

    std::cout << "Started server on 0.0.0.0:" << NETWORK_PORT << std::endl;
}

void NetworkServer::acceptLoopThread()
{
    while (true) {
        sf::TcpSocket* client_socket = new sf::TcpSocket();

        if (m_listener.accept(*client_socket) != sf::Socket::Done) {
            std::cerr << "WARN: accept failed" << std::endl;
            continue;
        }

        sf::Packet packet;
        if (client_socket->receive(packet) != sf::Socket::Done) {
            std::cerr << "WARN: connection with client lost" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }
        sf::Uint8 header;
        packet >> header;
        if (static_cast<Request>(header) != Request::Join) {
            std::cerr << "WARN: invalid join request" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }

        packet << static_cast<sf::Uint8>(Response::JoinOk);
        client_socket->send(packet);

        m_client_list.push_back(client_socket);
    }
}
