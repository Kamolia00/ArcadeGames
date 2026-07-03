@echo off
cd /d D:\ArcadeGamesByKamolia

D:\emsdk\upstream\emscripten\emcc.exe ^
-o index.html ^
main.cpp ^
"xo/xo.cpp" ^
"xo/menuXo.cpp" ^
"connect 4/connect4.cpp" ^
"connect 4/menuC4.cpp" ^
"player stuff/player.cpp" ^
"player stuff/valid_input.cpp" ^
"snake_game/snake/snake.cpp" ^
"snake_game/main_game/snake_game.cpp" ^
"snake_game/main_game/menu_snake.cpp" ^
"pong/pong game/pong.cpp" ^
"pong/pong game/ball.cpp" ^
"pong/menus/menu_pong.cpp" ^
-Wall ^
-std=gnu++14 ^
-D_DEFAULT_SOURCE ^
-Wno-missing-braces ^
-Os ^
-I. ^
-I C:/raylib/raylib/src ^
-I C:/raylib/raylib/src/external ^
-L. ^
-L C:/raylib/raylib/src ^
-s USE_GLFW=3 ^
-s ASYNCIFY ^
-s INITIAL_MEMORY=67108864 ^
-s FORCE_FILESYSTEM=1 ^
--preload-file assets ^
--shell-file shell.html ^
C:/raylib/raylib/src/libraylib.web.a ^
-DPLATFORM_WEB ^
-sEXPORTED_FUNCTIONS=_free,_malloc,_main ^
-s EXPORTED_RUNTIME_METHODS=ccall

if %ERRORLEVEL% neq 0 (
    echo.
    echo Build FAILED.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Build SUCCESS!
pause