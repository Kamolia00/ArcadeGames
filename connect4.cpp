#include"connect4.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include "valid_input.h"
connect4::connect4(Player &p1, Player &p2) : p1(p1), p2(p2) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            this->board[i][j] = ' ';
        }
    }
}

void connect4::display_board(){
   cout << "  1   2   3   4   5   6   7" << endl;
for(int i = 0; i < 7; i++){
    cout << "+---+---+---+---+---+---+---+" << endl;
    for(int j = 0; j < 7; j++){
        cout << "| " << board[i][j] << " ";
    }
    cout << "|" << endl;
}
cout << "+---+---+---+---+---+---+---+" << endl;
}
bool connect4::check_win(char symbol){    // start with rows
    for(int i = 0; i < 7; i++){
        for(int j = 0; j <= 3; j++){
            if(board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol && board[i][j+3] == symbol and symbol !=' '){
                 return true;
            }
        }
    }
    // check columns
    for(int j = 0; j < 7; j++){
        for(int i = 0; i <= 3; i++){
            if(board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol && board[i+3][j] == symbol and symbol !=' '){
                 return true;
            }
        }
    }
    // check diagonals
// check top-left to bottom-right
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol && board[i+3][j+3] == symbol and symbol !=' '){
                 return true;
            }
        }
    }
// check top-right to bottom-left
    for(int i = 0; i < 4; i++){
        for(int j = 3; j < 7; j++){
            if(board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol && board[i+3][j-3] == symbol and symbol !=' '){
                 return true;
            }
        }
    }
    return false;
}
bool connect4::check_draw(){
   for(int i=0;i<7;i++){
    if(board[0][i] == ' '){
        return false;
    }
   }
    return true;
}
void connect4::player_move(Player &player){
    int col,row=-1;
        cout << player.getName() << " (" << player.getSymbol() << ") - Enter column (1-7): ";
        cin >> col;
    if (cin.fail()) {
        input(col);
    }
        while(col < 1 or col > 7 or board[0][col-1] != ' '){
            cout << "Invalid column. Please try again." << endl;
            input(col);
        }
        for(int i = 6; i >= 0; i--){
            if(board[i][col-1] == ' '){
                board[i][col-1] = player.getSymbol();
                row = i;
                break;
            }
        }
    }
void connect4::play_game(){
    while(true){
        display_board();
        player_move(p1);
        if(check_win(p1.getSymbol())){
            display_board();
            cout << p1.getName() << " wins!" << endl;
            p1.incrementScore();
            break;
        }
        if(check_draw()){
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
        display_board();
        player_move(p2);
        if(check_win(p2.getSymbol())){
            display_board();
            cout << p2.getName() << " wins!" << endl;
            p2.incrementScore();
            break;
        }
        if(check_draw()){
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}
void connect4::vs_ai_easy() {
    while (true) {
        display_board();
        player_move(p1);
        if (check_win(p1.getSymbol())) {
            display_board();
            cout << p1.getName() << " wins!" << endl;
            p1.incrementScore();
            break;
        }
        if (check_draw()) {
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
        int col;
        do {
            col = rand() % 7;
        } while (board[0][col] != ' ');
        for (int i = 6; i >= 0; i--) {
            if (board[i][col] == ' ') {
                board[i][col] = p2.getSymbol();
                break;
            }
        }
        if (check_win(p2.getSymbol())) {
            display_board();
            cout << p2.getName() << " wins!" << endl;
            p2.incrementScore();
            break;
        }
        if (check_draw()) {
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

