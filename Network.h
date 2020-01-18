#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/TcpListener.hpp>

#include <string>
#include <vector>

class Network {
public:
    enum class Mode {Singleplayer, Server, Client};

    Network(Mode mode, const sf::IpAddress& ip);

private:
    static const unsigned short int NETWORK_PORT = 23402;

    sf::TcpSocket m_main_socket;
    sf::TcpListener m_listener;

    std::vector<sf::TcpSocket> m_clients_list;

    void updateLoop(unsigned int interval_ms);
    void acceptLoop();
};