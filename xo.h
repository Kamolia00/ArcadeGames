#ifndef XO_H
#define XO_H
#include "player.h"
class XO{
private:
Player &player1;
Player &player2;
char board[3][3];
bool checkWin(char symbol);
bool checkDraw();
void displayBoard();
void playerMove(Player &player);
int minimax(bool isMax);
void bestMove();
public:
XO(Player &p1, Player &p2);
void playGame();
void vsai();
};
#endif