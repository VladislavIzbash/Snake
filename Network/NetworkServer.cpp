#include "NetworkServer.h"

#include "Network.h"
#include "../Logger.h"
#include "../Settings.h"

#include <SFML/Network.hpp>

#include <thread>
#include <memory>
#include <iostream>

void NetworkServer::setup(const sf::IpAddress &ip_address)
{
    if (m_listener.listen(settings::NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't bind to port");

    (new std::thread(&NetworkServer::acceptLoopThread, this))->detach();

    Logger(Priority::Info) << "Started server on 0.0.0.0:" << settings::NETWORK_PORT << std::endl;
}

void NetworkServer::acceptLoopThread()
{
    while (true) {
        std::unique_ptr<sf::TcpSocket> client_socket = std::make_unique<sf::TcpSocket>();
        sf::Uint8 header = 0;
        sf::Packet packet;

        if (m_listener.accept(*client_socket) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Client accept failed" << std::endl;
            continue;
        }

        if (client_socket->receive(packet) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Connection with client lost" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }

        packet >> header;
        if (header != static_cast<sf::Uint8>(Request::Join)) {
            Logger(Priority::Warning) << "Invalid join request" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }

        packet << static_cast<sf::Uint8>(Response::JoinOk);
        client_socket->send(packet);

        m_client_list.push_back(std::move(client_socket));
        Logger(Priority::Info) << "Player #" << m_client_list.size() << " accepted" << std::endl;
    }
}



sf::Packet NetworkServer::buildUpdatePacket(std::vector<std::unique_ptr<GameObject>>& object_list) {
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(Response::UpdateOk);

    for (std::unique_ptr<GameObject>& obj: object_list) {
        packet << static_cast<sf::Uint8>(obj->getID());
        packet << static_cast<sf::Uint8>(obj->getType());
        *obj >> packet;
    }

    return packet;
}

void NetworkServer::update(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    sf::Packet packet;
    sf::Uint8 header = 0;

    for (std::unique_ptr<sf::TcpSocket>& client: m_client_list) {
        client->receive(packet);

        if (packet >> header && header == static_cast<sf::Uint8>(Request::UpdateState)) {
            sf::Packet resp = buildUpdatePacket(object_list);
            client->send(resp);
        }
    }
}
