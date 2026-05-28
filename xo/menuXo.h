#ifndef menu_h
#define menu_h
#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"

int showmenu();

int showAiMenu();

// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerName(Player &p, const std::string &prompt);

// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerSymbol(Player &p, std::string prompt);

int showPostGameMenu(Player & p1, Player & p2);
#endif
