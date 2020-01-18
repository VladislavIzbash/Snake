#include "Core/Network/Network.h"
#include "Core/Network/NetworkLocal.h"
#include "Core/Network/NetworkServer.h"
#include "Core/Network/NetworkClient.h"
#include "Renderer.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>


static const int WINDOW_SIZE = 800;

int main(int argc, char** argv)
{
    INetwork* network = nullptr;
    try {
        if (argc == 1) {
            network = new NetworkLocal();

        } else if (std::string(argv[1]) == "0.0.0.0") {
            network = new NetworkServer();
            network->setup("");

        } else {
            network = new NetworkClient();
            network->setup(sf::IpAddress(argv[1]));

        }
    } catch (std::runtime_error& error) {
        std::cerr << "FATAL: " << error.what() << std::endl;
        return 1;
    }

    sf::RenderWindow main_window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Snake alpha");
    main_window.setVerticalSyncEnabled(true);
    Renderer renderer(main_window);

    while (main_window.isOpen()) {
        sf::Event event{};
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                main_window.close();
        }

        renderer.drawAll();
    }

    return 0;
}
