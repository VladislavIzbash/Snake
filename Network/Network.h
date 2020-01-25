#pragma once

#include "../GameObject.h"

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

#include <string>
#include <map>


enum class Request {
    Join, UpdateState
};
enum class Response {
    JoinOk, UpdateOk
};

/*
 *  Интерфейс для сетевых классов. Обобщает функционал клиента, сервера и одиночной игры.
 */
class INetwork {
public:
    virtual void setup(const sf::IpAddress& ip_address) = 0;

    virtual void initObjectList(std::vector<std::unique_ptr<GameObject>>& object_list) = 0;

    virtual GameObject& getMyPlayer(std::vector<std::unique_ptr<GameObject>>& object_list) = 0;

    virtual void update(std::vector<std::unique_ptr<GameObject>>& object_list) = 0;
};