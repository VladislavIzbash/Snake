#include "Game/Game.h"
#include "Game/Singleplayer.h"
#include "Game/Server.h"
#include "Game/Client.h"
#include "Util.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <thread>


void updateThread(IGame* game)
{
    while (true) {
        game->update();

        std::this_thread::sleep_for(std::chrono::milliseconds(util::cfg::UPDATE_INTERVAL_MS));
    }
}

int main(int argc, char** argv)
{
    util::res::loadAll();

    IGame* game = nullptr;
    try {
        if (argc == 1) {
            game = new Singleplayer();
        } else if (std::string(argv[1]) == "-server") {
            game = new Server();
        } else {
            game = new Client(argv[1]);
        }
    } catch (std::runtime_error& error) {
        util::Logger(util::Priority::Critical) << error.what() << std::endl;
        return 1;
    }

    sf::RenderWindow main_window(sf::VideoMode(util::cfg::WINDOW_SIZE, util::cfg::WINDOW_SIZE), "Snake alpha");
    main_window.setVerticalSyncEnabled(true);

    std::thread update_thread(updateThread, game);
    update_thread.detach();

    while (main_window.isOpen()) {
        sf::Event event{};
        while (main_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    main_window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::W) game->getLocalPlayer().turn(util::Direction::Up);
                    if (event.key.code == sf::Keyboard::A) game->getLocalPlayer().turn(util::Direction::Left);
                    if (event.key.code == sf::Keyboard::S) game->getLocalPlayer().turn(util::Direction::Down);
                    if (event.key.code == sf::Keyboard::D) game->getLocalPlayer().turn(util::Direction::Right);
            }
        }

        main_window.clear(util::cfg::BACKGROUND_COLOR);
        game->render(main_window);
        main_window.display();
    }

    return 0;
}
