#ifndef xo_h
#define xo_h
#include "player.h"
void displayBoard(char board[3][3]);
void gameLoop();
bool winCheck(char board[3][3], char symbol);
bool drawCheck(char board[3][3]);

#endif