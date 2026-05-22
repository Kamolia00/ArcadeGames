#ifndef menu_h
#define menu_h
#include"player.h"
#include<iostream>
#include"raylib.h"
int showmenu();
int showAiMenu();
std::string getPlayerName(Player &p , const std::string& prompt);
void getPlayerSymbol(Player &p,std::string prompt);
int showPostGameMenu(Player &p1,Player &p2);
#endif