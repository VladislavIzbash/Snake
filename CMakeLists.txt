cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(snake
        src/Main.cpp
        src/Network/Network.h
        src/Game.cpp
        src/Game.h
        src/Renderer.cpp
        src/Renderer.h
        src/Network/NetworkClient.cpp
        src/Network/NetworkClient.h
        src/Network/NetworkLocal.cpp
        src/Network/NetworkLocal.h
        src/Network/NetworkServer.cpp
        src/Network/NetworkServer.h
        src/Util/Logger.cpp
        src/Util/Logger.h
        src/Entity/Entity.h
        src/Entity/SnakeBodyPart.cpp
        src/Entity/SnakeBodyPart.h
        src/Entity/Snake.cpp
        src/Entity/Snake.h
        src/Util/Config.h
        src/Entity/Entity.cpp
        src/Util/Resource.cpp
        src/Util/Resource.h src/Util/Grid.cpp src/Util/Grid.h)
target_link_libraries(snake pthread sfml-graphics sfml-window sfml-system sfml-network)
