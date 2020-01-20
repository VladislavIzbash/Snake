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

class INetwork {
public:
    virtual void setup(const sf::IpAddress& ip_address) = 0;

    virtual void initObjectList(std::map<unsigned int, IObject>& object_list) = 0;


};