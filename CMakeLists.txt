cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(snake
        src/Main.cpp
        src/Game/Game.h
        src/World.cpp
        src/World.h
        src/Util.cpp
        src/Util.h

        src/Entity/Entity.h
        src/Entity/SnakeBodyPart.cpp
        src/Entity/SnakeBodyPart.h
        src/Entity/Snake.cpp
        src/Entity/Snake.h
        src/Entity/Entity.cpp

        src/Game/Singleplayer.cpp
        src/Game/Singleplayer.h
        src/Game/Server.cpp
        src/Game/Server.h
        src/Game/Client.cpp
        src/Game/Client.h src/Entity/Fruit.cpp src/Entity/Fruit.h)
target_link_libraries(snake pthread sfml-graphics sfml-window sfml-system sfml-network)
