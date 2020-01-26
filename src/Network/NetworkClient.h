#pragma once

#include "Network.h"
#include "../Entity/Entity.h"

#include <SFML/Network/TcpSocket.hpp>

#include <memory>


class NetworkClient: public INetwork {
public:
    explicit NetworkClient(const std::string& address);

    void initEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) override;

    void updateEntityList(std::vector<std::unique_ptr<Entity>>& entity_list) override;

    Entity& getMyPlayer(const std::vector<std::unique_ptr<Entity>>& entity_list) override;

private:
    sf::TcpSocket m_socket;
    unsigned int m_myID;


    static void syncWithServer(std::vector<std::unique_ptr<Entity>>& entity_list, sf::Packet& packet);


};