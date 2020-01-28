#include "NetworkServer.h"

#include "../Util/Config.h"
#include "../Util/Logger.h"

#include <SFML/Network.hpp>

#include <cstdlib>


NetworkServer::NetworkServer()
{
    m_listener.setBlocking(false);

    if (m_listener.listen(cfg::NETWORK_PORT) != sf::Socket::Done) {
        throw std::runtime_error("Couldn't bind to port");
    }

    Logger(Priority::Info) << "Started server on 0.0.0.0:" << cfg::NETWORK_PORT << std::endl;
}

void NetworkServer::updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list)
{
    handleNewConnections(entity_list);

    for (auto client_it = m_client_list.begin(); client_it != m_client_list.end();) {
        sf::Packet packet;
        sf::Uint8 header;

        if (client_it->socket->receive(packet) == sf::Socket::Done) {
            if (packet >> header && header == (sf::Uint8)Request::UpdateState) {
                if (!packet.endOfPacket()) updatePlayerEntity(entity_list, client_it->id, packet);

                sf::Packet resp = buildUpdatePacket(entity_list);
                client_it->socket->send(resp);
            }

            client_it++;
        } else {
            Logger(Priority::Info) << "Player " << client_it->id << " disconnected" << std::endl;
            removePlayer(entity_list, client_it->id);

            m_client_list.erase(client_it);
        }
    }
}


void NetworkServer::handleNewConnections(std::vector<std::unique_ptr<Entity>>& object_list)
{
    Client client = {std::make_shared<sf::TcpSocket>(), static_cast<unsigned int>(rand()) + 1};

    if (m_listener.accept(*client.socket) == sf::Socket::Done) {
        sf::Uint8 header = 0;
        sf::Packet packet;

        if (client.socket->receive(packet) != sf::Socket::Done) {
            Logger(Priority::Warning) << "Client accept failed" << std::endl;
        } else if (packet >> header && header != (sf::Uint8)Request::Join) {
            Logger(Priority::Warning) << "Invalid join request" << " (" << client.id << ")" << std::endl;
        } else {
            packet.clear();

            if (spawnPlayer(object_list, client.id)) {
                packet << (sf::Uint8) Response::JoinOk << (sf::Uint32) client.id;
                client.socket->send(packet);

                Logger(Priority::Info) << "Player " << client.id << " accepted" << std::endl;
                m_client_list.push_back(client);
            } else {
                packet << (sf::Uint8) Response::JoinFailure;
                client.socket->send(packet);

                Logger(Priority::Info) << "Player " << client.id << " is not accepted (board is full)" << std::endl;
            }
        }
    }
}

sf::Packet NetworkServer::buildUpdatePacket(std::vector<std::unique_ptr<Entity>>& entity_list) {
    sf::Packet packet;
    packet << (sf::Uint8)Response::UpdateOk << (sf::Uint16)entity_list.size();

    for (auto& entity: entity_list) {
        packet << (sf::Uint32)entity->getID() << (sf::Uint8)entity->getType();
        entity->toPacket(packet);
    }


    return packet;
}

void NetworkServer::updatePlayerEntity(std::vector<std::unique_ptr<Entity>>& entity_list, unsigned int id, sf::Packet& packet)
{
    for (auto& entity: entity_list) {
        if (entity->getID() == id) entity->fromPacket(packet);
    }
}






