#include"xo.h"
#include"valid_input.h"
using namespace std;
XO::XO(Player &p1, Player &p2) : player1(p1), player2(p2) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
bool XO::checkWin(char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return true;
        }
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }
    return false;
}
bool XO::checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}
void XO::displayBoard() {
  cout << "    1   2   3" << endl;
  for(int i = 0; i < 3; i++) {
    cout << "  -------------" << endl;
    cout << i + 1 << " |";
    for (int j = 0; j < 3; j++) {
      cout << " " << board[i][j] << " |";
    }
    cout << endl;
  }
        cout << "  -------------" << endl;
}
void XO::playerMove(Player &player) {
    int row, col;
    cout << player.getName() << " (" << player.getSymbol() << ") - Enter your move (row and column): ";
    while (true) {
        cin >> row >> col;
        if (cin.fail()) {
            input(row);
            input(col);
        }
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = player.getSymbol();
            break;
        } else {
            cout << "Invalid move. Please try again." << endl;
        }
    }
}
void XO::playGame() {
    while (true) {
        displayBoard();
        playerMove(player1);
        if (checkWin(player1.getSymbol())) {
            displayBoard();
            cout << player1.getName() << " wins!" << endl;
            player1.incrementScore();
            break;
        }
        if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
        displayBoard();
        playerMove(player2);
        if (checkWin(player2.getSymbol())) {
            displayBoard();
            cout << player2.getName() << " wins!" << endl;
            player2.incrementScore();
            break;
        }
        if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}
int XO::minimax(bool isMax){
    if(checkWin(player2.getSymbol())){
        return 10;
    }
    if(checkWin(player1.getSymbol())){
        return -10;
    }
    if(checkDraw()){
        return 0;
    }
if(isMax){
 int best=-10;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j]=player2.getSymbol();
                best=max(best,minimax(false));
                board[i][j]=' ';
            }
        }
    }
    return best;   
}
else{
    int best=10;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j]=player1.getSymbol();
                best=min(best,minimax(true));
                board[i][j]=' ';
            }
        }
    }
    return best;
}
}
void XO::bestMove(){
    int bestVal=-10;
    int row=-1,col=-1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==' '){
                board[i][j]=player2.getSymbol();
                int moveVal=minimax(false);
                board[i][j]=' ';
                if(moveVal>bestVal){
                    row=i;
                    col=j;
                    bestVal=moveVal;
                }
            }
        }
    }
    board[row][col]=player2.getSymbol();
}
void XO::vsai_hard(){
    while (true) {
        if (player1.getSymbol() == 'X') {
            displayBoard();
            playerMove(player1);
            if (checkWin(player1.getSymbol())) {
                displayBoard();
                cout << player1.getName() << " wins!" << endl;
                player1.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
            bestMove();
            if (checkWin(player2.getSymbol())) {
                displayBoard();
                cout << "ai wins!" << endl;
                player2.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
        }
        else{
            bestMove();
            displayBoard();
            if (checkWin(player2.getSymbol())) {
                displayBoard();
                cout << "ai wins!" << endl;
                player2.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
            playerMove(player1);
            if (checkWin(player1.getSymbol())) {
                displayBoard();
                cout << player1.getName() << " wins!" << endl;
                player1.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
        }
    }
}
void XO::vsai_easy(){
    while (true) {
        if (player1.getSymbol() == 'X') {
            displayBoard();
            playerMove(player1);
            if (checkWin(player1.getSymbol())) {
                displayBoard();
                cout << player1.getName() << " wins!" << endl;
               player1.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
            int row, col;
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (board[row][col] != ' ');
            board[row][col] = player2.getSymbol();
            if (checkWin(player2.getSymbol())) {
                displayBoard();
                cout << "ai wins!" << endl;
                player2.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
        }
        else{
            int row, col;
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (board[row][col] != ' ');
            board[row][col] = player2.getSymbol();
            displayBoard();
            if (checkWin(player2.getSymbol())) {
                displayBoard();
                cout << "ai wins!" << endl;
                player2.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
            playerMove(player1);
            if (checkWin(player1.getSymbol())) {
                displayBoard();
                cout << player1.getName() << " wins!" << endl;
player1.incrementScore();
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
        }
    }
}