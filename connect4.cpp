#include"connect4.h"
#include<iostream>
connect4::connect4(Player &p1, Player &p2){
    this->p1 = p1;
    this->p2 = p2;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            this->board[i][j] = ' ';
        }
    }
}
void connect4::display_board(){
   cout << "    1   2   3   4   5   6   7" << endl;
    for(int i = 0; i < 7; i++){
        cout << "  +---+---+---+---+---+---+---+" << endl;
        cout << i+1 << " ";
        for(int j = 0; j < 7; j++){
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "  +---+---+---+---+---+---+---+" << endl;
}
bool connect4::check_win(char symbol){
    // start with rows
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
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(board[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}
void connect4::player_move(Player &player){
    int col,row=-1;
        cout << player.getName() << " (" << player.getSymbol() << ") - Enter column (1-7): ";
        cin >> col;
        while(col < 1 or col > 7){
            cout << "Invalid column. Please try again." << endl;
            cin >> col;
        }
        for(int i = 6; i >= 0; i--){
            if(board[i][col-1] == ' '){
                board[i][col-1] = player.getSymbol();
                row = i;
                break;
            }
        }
        while(row == -1){
            
    cout << "Column is full. Please choose another column: ";
    cin >> col;
    while(col < 1 || col > 7){
        cout << "Invalid column. Please enter a number between 1 and 7: ";
        cin >> col;
    }
    for(int i = 6; i >= 0; i--){
        if(board[i][col-1] == ' '){
            board[i][col-1] = player.getSymbol();
            row = i;
            break;
        }
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