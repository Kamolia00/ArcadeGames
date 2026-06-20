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
        "snake_game/snake/snake.cpp"    "snake_game/snake/snake.h"
        snake_game/snake/constants.h
        "snake_game/main_game/snake_game.cpp" "snake_game/main_game/snake_game.h"
        "snake_game/main_game/menu_snake.cpp" "snake_game/main_game/menu_snake.h"
        "pong/pong game/ball.cpp" "pong/pong game/ball.h"
        "pong/pong game/pong.cpp" "pong/pong game/pong.h"
        pong/menus/menu_pong.h
        pong/menus/menu_pong.cpp
)

target_link_libraries(ArcadeGames raylib winmm gdi32 opengl32)

add_custom_command(TARGET ArcadeGames POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ArcadeGames>/assets
)