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
int connect4::minimax(int depth, bool isMax, int alpha, int beta) {
    if(depth == 0 || check_win(p1.getSymbol()) || check_win(p2.getSymbol()) || check_draw()) {
        if(check_win(p2.getSymbol())) return depth + 10;
        else if(check_win(p1.getSymbol())) return -1*(depth + 10);
        else return 0;
    }
    if(isMax){
        int best=-1000;
        for(int i=0;i<7;i++){
            if(board[0][i] == ' '){
                int row;
                for(row=6;row>=0;row--){
                    if(board[row][i] == ' '){
                        board[row][i] = p2.getSymbol();
                        break;
                    }
                }
                best=max(best,minimax(depth-1,false,alpha,beta));
                board[row][i] = ' ';
                alpha=max(alpha,best);
                if(beta <= alpha) break;
            }
        }
        return best;
    }
    else{
        int worst=1000;
        for(int i=0;i<7;i++){
            if(board[0][i] == ' '){
                int row;
                for(row=6;row>=0;row--){
                    if(board[row][i] == ' '){
                        board[row][i] = p1.getSymbol();
                        break;
                    }
                }
                worst=min(worst,minimax(depth-1,true,alpha,beta));
                board[row][i] = ' ';
                beta=min(beta,worst);
                if(beta <= alpha) break;
            }
        }
        return worst;
    }
}
int connect4::getBestMove(int depth) {
    int order[] = {3,2,4,1,5,0,6};
    int bestVal = -1000;
    int bestCol = -1;
    for(int k = 0; k < 7; k++){
        int i = order[k];
        if(board[0][i] == ' '){
            int row;
            for(row = 6; row >= 0; row--){
                if(board[row][i] == ' '){
                    board[row][i] = p2.getSymbol();
                    break;
                }
            }
            int moveVal = minimax(depth-1, false, -1000, 1000);
            board[row][i] = ' ';
            if(moveVal > bestVal){
                bestCol = i;
                bestVal = moveVal;
            }
        }
    }
    return bestCol;
}
void connect4::vs_ai_hard(){
    while(true){
        if(p1.getSymbol()=='X'){
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
        int bestCol = getBestMove(12);  // depth can be adjusted
        for (int i = 6; i >= 0; i--) {
            if (board[i][bestCol] == ' ') {
                board[i][bestCol] = p2.getSymbol();
                break;
            }
        }
        display_board();
        if (check_win(p2.getSymbol())) {
            display_board();
            cout <<"ai wins!" << endl;
            p2.incrementScore();
            break;
        }
        if (check_draw()) {
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
else{
        int bestCol = getBestMove(9);  // depth can be adjusted
        for (int i = 6; i >= 0; i--) {
            if (board[i][bestCol] == ' ') {
                board[i][bestCol] = p2.getSymbol();
                break;
            }
        }
        display_board();
        if (check_win(p2.getSymbol())) {
            display_board();
            cout <<"ai wins!" << endl;
            p2.incrementScore();
            break;
        }
        if (check_draw()) {
            display_board();
            cout << "It's a draw!" << endl;
            break;
        }
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
}    
}
}