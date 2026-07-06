#ifndef connect4_h
#define connect4_h
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "raylib.h"
using namespace std;
class connect4{
    private:
    Sound ClickSfx;
    bool getWinCells(char symbol,int cells[4][2]);
        Player &p1;
        Player &p2;
        bool check_win(char symbol);
        bool check_draw();
        void display_board();
        char board[7][7];
        void player_move(Player &player);
int minimax(int depth, bool isMax, int alpha, int beta);  // returns score
int getBestMove(int depth);  // calls minimax, returns best column
void draw_board();
public:
    connect4(Player &p1, Player &p2);
    ~connect4();
        void play_game();
        void vs_ai_easy();
    void vs_ai_hard();
    //
    void pvp_gui();
void ai_ez_gui();
    void ai_hard_gui();
};
#endif