#ifndef menuC4_h
#define menuC4_h
#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
int showmenu_c4();
int showAiMenu_c4();
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerName_c4(Player &p , const std::string& prompt);
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerSymbol_c4(Player &p,std::string prompt);
int showPostGameMenu_c4(Player &p1,Player &p2);



#endif