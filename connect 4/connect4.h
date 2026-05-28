#ifndef connect4_h
#define connect4_h
#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
using namespace std;
class connect4{
    private:
        Player &p1;
        Player &p2;
        bool check_win(char symbol);
        bool check_draw();
        void display_board();
        char board[7][7];
        void player_move(Player &player);
int minimax(int depth, bool isMax, int alpha, int beta);  // returns score
int getBestMove(int depth);  // calls minimax, returns best column
public:
void draw_board();
    connect4(Player &p1, Player &p2);
        void play_game();
        void vs_ai_easy();
    void vs_ai_hard();
    void pvp_gui();
void ai_ez_gui();
    void ai_hard_gui();
};
#endif