cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

add_executable(Snake Main.cpp Core/Network/Network.h Game.cpp Game.h Renderer.cpp Renderer.h Core/Network/NetworkClient.cpp Core/Network/NetworkClient.h Core/Network/NetworkLocal.cpp Core/Network/NetworkLocal.h Core/Network/NetworkServer.cpp Core/Network/NetworkServer.h)
target_link_libraries(Snake pthread sfml-graphics sfml-window sfml-system sfml-network)