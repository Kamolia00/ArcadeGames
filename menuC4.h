#ifndef menuC4_h
#define menuC4_h
#include "connect4.h"
#include "player.h"
#include "raylib.h"
int showmenu_c4();
int showAiMenu();
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerName(Player &p , const std::string& prompt);
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerSymbol(Player &p,std::string prompt);
int showPostGameMenu_c4(Player &p1,Player &p2);



#endif