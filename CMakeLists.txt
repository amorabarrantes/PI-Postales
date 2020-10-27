cmake_minimum_required(VERSION 3.17)
project(Proyecto_1 C)

set(CMAKE_C_STANDARD 99)

find_package(SFML 2.5 COMPONENTS graphics window system)

add_executable(Proyecto_1 main.c)
target_link_libraries(Proyecto_1 sfml-graphics sfml-audio sfml-window sfml-system csfml-graphics csfml-audio csfml-window csfml-system)