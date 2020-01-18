#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

#include <string>
#include <vector>


enum class Request {
    Join
};
enum class Response {
    JoinOk
};

class INetwork {
public:
    virtual void setup(const sf::IpAddress& ip_address) = 0;

protected:
    static const unsigned short int NETWORK_PORT = 23402;
};