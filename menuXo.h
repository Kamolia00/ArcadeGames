#ifndef menu_h
#define menu_h
#include"player.h"
#include<iostream>
#include"raylib.h"
int showmenu();
int showAiMenu();
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerName(Player &p , const std::string& prompt);
// return bool so caller can detect Back/cancel from the setup screens
bool getPlayerSymbol(Player &p,std::string prompt);
int showPostGameMenu(Player &p1,Player &p2);
#endif