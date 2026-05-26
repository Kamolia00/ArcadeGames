cmake_minimum_required(VERSION 4.2)
project(ArcadeGames)

set(CMAKE_CXX_STANDARD 14)

set(RAYLIB_DIR "D:/raylib-6.0_win64_mingw-w64")

include_directories(.)
include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)
add_executable(ArcadeGames
        player.cpp
        player.h
        xo.cpp
        xo.h
        connect4.cpp
        connect4.h
        valid_input.cpp
        main.cpp
        menuXo.h
        menuXo.cpp
        menuC4.h
        menuC4.cpp
)

target_link_libraries(ArcadeGames raylib winmm gdi32 opengl32)