#ifndef connect4_h
#define connect4_h
#include "player.h"
#include<vector>
using namespace std;
class connect4{
    private:
        Player p1;
        Player p2;
        bool check_win(char symbol);
        bool check_draw();
        void display_board();
        char board[7][7];
        void player_move(Player &player);
        public:
        connect4(Player &p1, Player &p2);
        void play_game();
        
};
#endif