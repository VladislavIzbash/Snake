#include "Client.h"

#include <SFML/Network.hpp>


Client::Client(const std::string& address): m_world(true)
{
    sf::Packet packet;
    sf::Uint8 header;

    if (m_socket.connect(sf::IpAddress(address), util::cfg::NETWORK_PORT) != sf::Socket::Done) {
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

        util::Logger(util::Priority::Info) << "Connected to " << address << ", my ID is " << m_myID << std::endl;
    } else {
        throw std::runtime_error("Server is full");
    }
}

void Client::update()
{
    sf::Packet packet;
    sf::Uint8 header;

    packet << (sf::Uint8)Request::UpdateState;
    try {
        m_world.getEntityById(m_myID).update();
        m_world.getEntityById(m_myID).toPacket(packet);
    } catch (std::runtime_error& error) {}

    m_socket.send(packet);
    packet.clear();

    if (m_socket.receive(packet) == sf::Socket::Done && packet >> header && header == (sf::Uint8)Response::UpdateOk) {
        m_world.fromPacket(packet);
    }


}

Snake& Client::getLocalPlayer()
{
    return dynamic_cast<Snake&>(m_world.getEntityById(m_myID));
}

void Client::render(sf::RenderTarget& target)
{
    for (auto& entity: m_world.getAllEntities()) {
        target.draw(*entity);
    }
}
