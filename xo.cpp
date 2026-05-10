#include"xo.h"
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
    while (true) {
        cout << player.getName() << " (" << player.getSymbol() << ") - Enter your move (row and column): ";
        cin >> row >> col;
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