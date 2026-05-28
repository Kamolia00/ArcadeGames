cmake_minimum_required(VERSION 4.2)
project(ArcadeGames)
set(CMAKE_CXX_STANDARD 14)
set(RAYLIB_DIR "D:/raylib-6.0_win64_mingw-w64")

include_directories(.)
include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

add_executable(ArcadeGames
        main.cpp

        xo/xo.cpp         xo/xo.h
        xo/menuXo.cpp     xo/menuXo.h

        "connect 4/connect4.cpp"   "connect 4/connect4.h"
        "connect 4/menuC4.cpp"     "connect 4/menuC4.h"

        "player stuff/player.cpp"       "player stuff/player.h"
        "player stuff/valid_input.cpp"  "player stuff/valid_input.h"
)

target_link_libraries(ArcadeGames raylib winmm gdi32 opengl32)