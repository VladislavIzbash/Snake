#include "NetworkServer.h"

#include "Network.h"
#include "../Logger.h"
#include "../../Settings.h"

#include <SFML/Network.hpp>

#include <thread>

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
        sf::TcpSocket* client_socket = new sf::TcpSocket();
        sf::Uint8 header;

        if (m_listener.accept(*client_socket) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Client accept failed" << std::endl;
            continue;
        }

        sf::Packet packet;
        if (client_socket->receive(packet) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Connection with client lost" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }

        packet >> header;
        if (static_cast<Request>(header) != Request::Join) {
            Logger(Priority::Warning) << "Invalid join request" << " (" << client_socket->getRemoteAddress() << ")" << std::endl;
            continue;
        }

        packet << static_cast<sf::Uint8>(Response::JoinOk);
        client_socket->send(packet);

        m_client_list.push_back(client_socket);
        Logger(Priority::Info) << "Player #" << m_client_list.size() << " accepted" << std::endl;
    }
}
