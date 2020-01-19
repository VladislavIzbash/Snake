cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(Snake Core/Main.cpp Core/Network/Network.h Core/Game.cpp Core/Game.h Core/Renderer.cpp Core/Renderer.h Core/Network/NetworkClient.cpp Core/Network/NetworkClient.h Core/Network/NetworkLocal.cpp Core/Network/NetworkLocal.h Core/Network/NetworkServer.cpp Core/Network/NetworkServer.h Core/Logger.cpp Core/Logger.h Core/GameObject.h BaseObjects/Background.cpp BaseObjects/Background.h Core/GameObject.cpp BaseObjects/SnakeSegment.cpp BaseObjects/SnakeSegment.h BaseObjects/Snake.cpp BaseObjects/Snake.h)
target_link_libraries(Snake pthread sfml-graphics sfml-window sfml-system sfml-network)
