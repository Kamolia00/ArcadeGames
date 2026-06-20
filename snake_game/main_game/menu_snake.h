#include <iostream>
#include "raylib.h"
#include "snake_game/snake/snake.h"
#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>

int showPostGame_menu(bool won, bool levelComplete, int level,
const std::map<std::string, int>& board);
int showmenu_snake();
bool getPlayerName_snake(Snake &snake, const std::string& prompt);
bool getPlayerColor_snake(Snake &snake, std::string prompt);