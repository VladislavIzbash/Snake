#include "NetworkClient.h"

#include "Network.h"
#include "../Logger.h"
#include "../Settings.h"
#include "../Snake/Snake.h"

#include <SFML/Network.hpp>
#include <iostream>


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
    packet >> m_my_id;

    Logger(Priority::Info) << "Connected to " << ip_address << ":" << settings::NETWORK_PORT << std::endl;
    Logger(Priority::Info) << "My ID: " << m_my_id << std::endl;
}

void NetworkClient::initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    update(object_list);
}

void NetworkClient::syncObjectList(std::vector<std::unique_ptr<GameObject>>& object_list, sf::Packet& packet)
{
    sf::Uint32 id = 0;
    sf::Uint8 type = 0;
    unsigned int i;

    for (i = 0; packet >> id >> type; i++) {
        if (i < object_list.size()) {
            if (object_list.at(i)->getID() == id) {
                *object_list.at(i) << packet;
            } else {
                object_list.at(i) = createObject(static_cast<ObjectType>(type), id);
                *object_list.at(i) << packet;
            }
        } else {
            object_list.push_back(createObject(static_cast<ObjectType>(type), id));
            *object_list.at(i) << packet;
        }
    }

    if (object_list.size() > i) {
        object_list.erase(object_list.begin() + i, object_list.end());
    }
}

void NetworkClient::update(std::vector<std::unique_ptr<GameObject>>& object_list)
{
    sf::Packet packet;
    sf::Uint8 header = 0;

    packet << static_cast<sf::Uint8>(Request::UpdateState);
    m_socket.send(packet);

    m_socket.receive(packet);
    packet >> header;

    if (header == static_cast<sf::Uint8>(Response::UpdateOk)) {
        syncObjectList(object_list, packet);
    }
}

unsigned int NetworkClient::getMyId() { return m_my_id; }
