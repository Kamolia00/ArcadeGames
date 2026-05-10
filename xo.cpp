#include "xo.h"
using namespace std;
void displayBoard(char board[3][3])
{
    std::cout << "    1   2   3" << std::endl;
      for (int i = 0; i < 3; i++) {
       std::cout << "  +---+---+---+" << std::endl;  // fixed: 4 segments
        std::cout << i + 1 << " ";
for (int j = 0; j < 3; j++) {
            std::cout << "| " << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "  +---+---+---+" << std::endl;
}
bool checkWin(char board[3][3],char symbol){
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
            return true;
        }
    }
    // Check diagonals
    // main 1st
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    // sub-main diagonal
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }
    return false;
}
bool drawCheck(char board[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; // Found an empty cell, not a draw
            }
        }
    }
    return true; // No empty cells, it's a draw
}

void gameLoop(Player &player1, Player &player2) {
    // Implementation for the game loop
    char board[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };
while(true){
    displayBoard(board);
    int row, col;
    std::cout<<player1.getName()<<"'s turn. Enter row and column (1-3): \n";
    std::cin>>row>>col;
    while(row < 1 || row > 3 || col < 1 || col > 3){
        std::cout<<"Invalid input. Please enter row and column between 1 and 3: \n";
        std::cin>>row>>col;
    }
    while(board[row-1][col-1] != ' '){
        std::cout<<"Cell already occupied. Please enter a different cell: \n";
        std::cin>>row>>col;
    }
    board[row-1][col-1] = player1.getSymbol();
    if(checkWin(board, player1.getSymbol())){
        displayBoard(board);
        std::cout<<player1.getName()<<" wins!\n";
        player1.incrementScore();
        break;
    }
    if(drawCheck(board)){
        displayBoard(board);
        std::cout<<"It's a draw!\n";
        break;
    }
    displayBoard(board);
    std::cout<<player2.getName()<<"'s turn. Enter row and column (1-3): \n";
    std::cin>>row>>col;
    while(row < 1 || row > 3 || col < 1 || col > 3){
        std::cout<<"Invalid input. Please enter row and column between 1 and 3: \n";
        std::cin>>row>>col;
    }
    while(board[row-1][col-1] != ' '){
        std::cout<<"Cell already occupied. Please enter a different cell: \n";
        std::cin>>row>>col;
    }
    board[row-1][col-1] = player2.getSymbol();
    if(checkWin(board, player2.getSymbol())){
        displayBoard(board);
        std::cout<<player2.getName()<<" wins!\n";
        player2.incrementScore();
        break;
    }
    if(drawCheck(board)){
        displayBoard(board);
        std::cout<<"It's a draw!\n";
        break;
    }
}
}