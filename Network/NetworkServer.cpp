#include "NetworkServer.h"

#include "Network.h"
#include "../Logger.h"
#include "../Settings.h"
#include "../Snake/Snake.h"

#include <SFML/Network.hpp>

#include <memory>
#include <cstdlib>


void NetworkServer::setup(const sf::IpAddress &ip_address)
{
    m_listener.setBlocking(false);

    if (m_listener.listen(settings::NETWORK_PORT) != sf::Socket::Done)
        throw std::runtime_error("Couldn't bind to port");


    Logger(Priority::Info) << "Started server on 0.0.0.0:" << settings::NETWORK_PORT << std::endl;
}

void NetworkServer::handleNewConnections(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    Client client = {std::make_shared<sf::TcpSocket>(), static_cast<unsigned int>(rand()) + 1};

    if (m_listener.accept(*client.socket) == sf::Socket::Done) {
        sf::Uint8 header = 0;
        sf::Packet packet;


        if (client.socket->receive(packet) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Client accept failed" << std::endl;
        } else if (packet >> header && header != static_cast<sf::Uint8>(Request::Join)) {
            Logger(Priority::Warning) << "Invalid join request" << " (" << client.socket->getRemoteAddress() << ")" << std::endl;
        } else {
            packet.clear();
            packet << static_cast<sf::Uint8>(Response::JoinOk) << static_cast<sf::Uint32>(client.id);
            client.socket->send(packet);

            Logger(Priority::Info) << "Player " << client.id << " accepted" << std::endl;
            m_client_list.push_back(client);

            addNewPlayer(object_list, client.id);
        }
    }
}



sf::Packet NetworkServer::buildUpdatePacket(std::vector<std::unique_ptr<GameObject>>& object_list) {
    sf::Packet packet;
    packet << static_cast<sf::Uint8>(Response::UpdateOk);

    for (std::unique_ptr<GameObject>& obj: object_list) {
        packet << static_cast<sf::Uint32>(obj-> getID()) << static_cast<sf::Uint8>(obj->getType());
        *obj >> packet;
    }

    return packet;
}

void NetworkServer::update(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    handleNewConnections(object_list);

    for (auto it = m_client_list.begin(); it != m_client_list.end();) {
        sf::Packet packet;
        sf::Uint8 header = 0;

        if (it->socket->receive(packet) == sf::Socket::Done) {
            if (packet >> header && header == static_cast<sf::Uint8>(Request::UpdateState)) {
                if (!packet.endOfPacket()) updatePlayerObject(object_list, it->id, packet);

                sf::Packet resp = buildUpdatePacket(object_list);
                it->socket->send(resp);
            }

            ++it;
        } else {
            Logger(Priority::Info) << "Player " << it->id << " disconnected" << std::endl;

            removePlayer(object_list, it->id);

            m_client_list.erase(it);
        }
    }
}

void NetworkServer::updatePlayerObject(std::vector<std::unique_ptr<GameObject>>& object_list, unsigned int id, sf::Packet& packet)
{
    for (auto& obj: object_list) {
        if (obj->getID() == id) *obj << packet;
    }
}
