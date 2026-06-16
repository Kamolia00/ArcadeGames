#include <iostream>
#include "raylib.h"
#include "snake_game/snake/snake.h"
#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"
int showmenu_snake();
int showPostGame_menu();
bool getPlayerName_snake(Snake &snake, const std::string& prompt);
bool getPlayerColor_snake(Snake &snake, std::string prompt);