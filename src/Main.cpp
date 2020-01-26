#include "Network/Network.h"
#include "Network/NetworkLocal.h"
#include "Network/NetworkServer.h"
#include "Network/NetworkClient.h"

#include "Util/Logger.h"
#include "Util/Config.h"
#include "Util/Resource.h"

#include "Entity/Snake.h"

#include "Game.h"
#include "Renderer.h"

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

        } else {
            network = new NetworkClient(argv[1]);
        }
    } catch (std::runtime_error& error) {
        Logger(Priority::Critical) << error.what() << std::endl;
        return 1;
    }

    sf::RenderWindow main_window(sf::VideoMode(cfg::WINDOW_SIZE, cfg::WINDOW_SIZE), "Snake alpha");
    main_window.setVerticalSyncEnabled(true);

    res::loadAll();
    Game game(*network);
    Renderer renderer(main_window, game);

    while (main_window.isOpen()) {
        sf::Event event{};
        while (main_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    main_window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::W) game.turnLocalPlayer(Direction::UP);
                    if (event.key.code == sf::Keyboard::A) game.turnLocalPlayer(Direction::LEFT);
                    if (event.key.code == sf::Keyboard::S) game.turnLocalPlayer(Direction::DOWN);
                    if (event.key.code == sf::Keyboard::D) game.turnLocalPlayer(Direction::RIGHT);
            }
        }

        renderer.drawAll();
    }

    return 0;
}
