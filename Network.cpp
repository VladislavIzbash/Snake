#include "Network.h"

#include <SFML/Network.hpp>

#include <iostream>
#include <thread>
#include <chrono>

Network::Network(Network::Mode mode, const sf::IpAddress& ip)
{
    switch (mode) {
        case Mode::Singleplayer:
            std::cout << "Started in singleplayer mode\n";
            break;
        case Mode::Server:
            if (m_listener.listen(NETWORK_PORT) != sf::Socket::Done)
                throw std::runtime_error("Couldn't bind to port");

            std::cout << "Started server on 0.0.0.0:" << NETWORK_PORT << std::endl;
            break;
        case Mode::Client:
            if (m_main_socket.connect(ip, NETWORK_PORT) != sf::Socket::Done)
                throw std::runtime_error("Couldn't connect to server");

            std::cout << "Connected to " << ip << ":" << NETWORK_PORT << std::endl;
            break;
    }

}

