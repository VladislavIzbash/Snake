#include "NetworkClient.h"

#include "../Util/Config.h"
#include "../Util/Logger.h"
#include "../Entity/Snake.h"

#include <SFML/Network.hpp>


NetworkClient::NetworkClient(const std::string& address)
{
    sf::Packet packet;
    sf::Uint8 header;

    if (m_socket.connect(address, cfg::NETWORK_PORT) != sf::Socket::Done) {
        throw std::runtime_error("Couldn't connect to server");
    }

    packet << (sf::Uint8)Request::Join;
    m_socket.send(packet);
    packet.clear();

    if (m_socket.receive(packet) != sf::Socket::Done) {
        throw std::runtime_error("Connection failed");
    }

    packet >> header;
    if (header == (sf::Uint8)Response::JoinOk) {
        packet >> m_myID;

        Logger(Priority::Info) << "Connected to " << address << ", my ID is " << m_myID << std::endl;
    } else {
        throw std::runtime_error("Server denied us");
    }
}


void NetworkClient::initEntityList(std::vector<std::unique_ptr<Entity>>& entity_list)
{
    updateEntityList(entity_list);
}

void NetworkClient::updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list)
{
    sf::Packet packet;
    sf::Uint8 header = 0;

    packet << (sf::Uint8)Request::UpdateState;
    try {
        getMyPlayer(entity_list).toPacket(packet);
    } catch (std::runtime_error& error) {
        Logger(Priority::Warning) << error.what() << std::endl;
    }
    m_socket.send(packet);
    packet.clear();

    if (m_socket.receive(packet) == sf::Socket::Done && packet >> header && header == (sf::Uint8)Response::UpdateOk) {
        syncWithServer(entity_list, packet);
    }
}

Entity& NetworkClient::getMyPlayer(const std::vector<std::unique_ptr<Entity>>& entity_list)
{
    for (auto& entity: entity_list) {
        if (entity->getID() == m_myID) return *entity;
    }
    throw std::runtime_error("My player is missing");
}


void NetworkClient::syncWithServer(std::vector<std::unique_ptr<Entity>>& entity_list, sf::Packet& packet)
{
    sf::Uint16 new_size;
    sf::Uint32 id;
    sf::Uint8 type;

    packet >> new_size;
    for (auto entity_it = entity_list.begin(); entity_it != entity_list.end(); entity_it++) {
        packet >> id >> type;

        if (entity_it->get()->getID() == id) {
            entity_it->get()->fromPacket(packet);
        } else {
            entity_list.erase(entity_it);
            entity_list.emplace(entity_it, createEntity(static_cast<EntityType>(type), id));
            entity_it->get()->fromPacket(packet);
        }
    }

    if (new_size <= entity_list.size()) {
        entity_list.resize(new_size);
    } else {
        while (packet >> id >> type) {
            entity_list.emplace_back(createEntity(static_cast<EntityType>(type), id));
            entity_list.back()->fromPacket(packet);
        }
    }
}



