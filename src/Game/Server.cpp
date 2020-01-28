#include "Server.h"

#include <SFML/Network/TcpSocket.hpp>


Server::Server(): Singleplayer()
{
    m_listener.setBlocking(false);

    if (m_listener.listen(util::cfg::NETWORK_PORT) != sf::Socket::Done) {
        throw std::runtime_error("Couldn't bind to port");
    }

    util::Logger(util::Priority::Info) << "Started server on 0.0.0.0:" << util::cfg::NETWORK_PORT << std::endl;
}

void Server::update()
{
    handleNewConnections();

    for (auto client_it = m_clientList.begin(); client_it != m_clientList.end();) {
        if (!handleUpdateRequest(*client_it)) {
            util::Logger(util::Priority::Info) << "Player " << client_it->id << " disconnected" << std::endl;
            m_world.removeEntityById(client_it->id);

            m_clientList.erase(client_it);

        } else {
            client_it++;
        }
    }

    Singleplayer::update();
}

void Server::handleNewConnections()
{
    Client client = {std::make_shared<sf::TcpSocket>(), static_cast<unsigned int>(rand()) + 1};

    if (m_listener.accept(*client.socket) == sf::Socket::Done) {
        sf::Uint8 header = 0;
        sf::Packet packet;

        if (client.socket->receive(packet) != sf::Socket::Done) {
            util::Logger(util::Priority::Warning) << "Client accept failed" << std::endl;
        } else if (packet >> header && header != (sf::Uint8)Request::Join) {
            util::Logger(util::Priority::Warning) << "Invalid join request" << " (" << client.id << ")" << std::endl;
        } else {
            packet.clear();

            if (m_world.trySpawnSnake(client.id)) {
                packet << (sf::Uint8) Response::JoinOk << (sf::Uint32) client.id;
                client.socket->send(packet);

                util::Logger(util::Priority::Info) << "Player " << client.id << " accepted" << std::endl;
                m_clientList.push_back(client);
            } else {
                packet << (sf::Uint8) Response::JoinFull;
                client.socket->send(packet);

                util::Logger(util::Priority::Info) << "Player " << client.id << " is not accepted (No space left)" << std::endl;
            }
        }
    }
}

bool Server::handleUpdateRequest(Client& client)
{
    sf::Packet packet;
    sf::Uint8 header;

    if (client.socket->receive(packet) != sf::Socket::Done) {
        return false;
    }

    if (packet >> header && header == (sf::Uint8)Request::UpdateState) {
        if (!packet.endOfPacket()) m_world.getEntityById(client.id).fromPacket(packet);

        packet.clear();
        packet << (sf::Uint8)Response::UpdateOk;
        m_world.toPacket(packet);
        client.socket->send(packet);
    }

    return true;
}

