#include "Network/Network.h"
#include "Network/NetworkLocal.h"
#include "Network/NetworkServer.h"
#include "Renderer.h"
#include "Logger.h"
#include "Settings.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

#include <string>


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
            //network = new NetworkClient();
            //network->setup(sf::IpAddress(argv[1]));

        }
    } catch (std::runtime_error& error) {
        Logger(Priority::Critical) << error.what() << std::endl;
        return 1;
    }

    sf::RenderWindow main_window(sf::VideoMode(settings::WINDOW_SIZE, settings::WINDOW_SIZE), "Snake alpha");
    main_window.setVerticalSyncEnabled(true);

    Game game(*network);
    Renderer renderer(main_window, game);

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
