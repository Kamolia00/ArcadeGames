#ifndef XO_H
#define XO_H

#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "raylib.h"
extern Font font;
class XO{
private:
bool GetWinCells(char Symbol,int cells[3][2]);
    Sound clickSfx;
Player &player1;
Player &player2;
char board[3][3];
bool checkWin(char symbol);
bool checkDraw();
void displayBoard();
void playerMove(Player &player);
int minimax(bool isMax);
void bestMove();
    void drawBoard();
public:
XO(Player &p1, Player &p2);
~XO();
void playGame();
void vsai_hard();
void vsai_easy();
    void playGameGUI_pvp();
void playGameGUI_ai_easy();
    void playGameGUI_ai_hard();
};
#endif