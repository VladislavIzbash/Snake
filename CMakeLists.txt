cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(Snake
        Main.cpp
        Network/Network.h
        Game.cpp
        Game.h
        Renderer.cpp
        Renderer.h
        Network/NetworkClient.cpp
        Network/NetworkClient.h
        Network/NetworkLocal.cpp
        Network/NetworkLocal.h
        Network/NetworkServer.cpp
        Network/NetworkServer.h
        Logger.cpp
        Logger.h
        GameObject.h
        Snake/SnakeSegment.cpp
        Snake/SnakeSegment.h
        Snake/Snake.cpp
        Snake/Snake.h
        Settings.h GameObject.cpp)
target_link_libraries(Snake pthread sfml-graphics sfml-window sfml-system sfml-network)
