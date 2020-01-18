cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

add_executable(Snake Main.cpp Network.h Network.cpp Game.cpp Game.h Renderer.cpp Renderer.h)
target_link_libraries(Snake pthread sfml-graphics sfml-window sfml-system sfml-network)