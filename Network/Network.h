#pragma once

#include "../Object.h"

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

#include <string>
#include <map>


enum class Request {
    Join
};
enum class Response {
    JoinOk
};

/*
 *  Интерфейс для сетевых классов. Обобщает функционал клиента, сервера и одиночной игры.
 */
class INetwork {
public:
    virtual void setup(const sf::IpAddress& ip_address) = 0;

    virtual void initObjectList(std::vector<std::unique_ptr<IObject>>& object_list) = 0;

};