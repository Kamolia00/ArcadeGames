cmake_minimum_required(VERSION 4.2)
project(ArcadeGames)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ArcadeGames
        player.cpp
        player.h
        xo.cpp
        xo.h
        connect4.cpp
        valid_input.cpp
)
