#include"xo.h"
#include"valid_input.h"
#include<raylib.h>
using namespace std;
//const
XO::XO(Player &p1, Player &p2) : player1(p1), player2(p2) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
//common
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
//terminal game
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
//ai
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
//gui
void XO::drawBoard() {
    int startX = 490, startY = 210;
    int cellSize = 100;
    int gridSize = 300;
    Color lineColor = {100, 200, 255, 255};
    int thickness = 3;

    // borderlines
    DrawLineEx({(float)startX, (float)startY}, {(float)(startX + gridSize), (float)startY}, thickness, lineColor);                          // top
    DrawLineEx({(float)startX, (float)(startY + gridSize)}, {(float)(startX + gridSize), (float)(startY + gridSize)}, thickness, lineColor); // bottom
    DrawLineEx({(float)startX, (float)startY}, {(float)startX, (float)(startY + gridSize)}, thickness, lineColor);                          // left
    DrawLineEx({(float)(startX + gridSize), (float)startY}, {(float)(startX + gridSize), (float)(startY + gridSize)}, thickness, lineColor); // right

    // inner lines
    DrawLineEx({(float)(startX + cellSize), (float)startY}, {(float)(startX + cellSize), (float)(startY + gridSize)}, thickness, lineColor);
    DrawLineEx({(float)(startX + cellSize*2), (float)startY}, {(float)(startX + cellSize*2), (float)(startY + gridSize)}, thickness, lineColor);
    DrawLineEx({(float)startX, (float)(startY + cellSize)}, {(float)(startX + gridSize), (float)(startY + cellSize)}, thickness, lineColor);
    DrawLineEx({(float)startX, (float)(startY + cellSize*2)}, {(float)(startX + gridSize), (float)(startY + cellSize*2)}, thickness, lineColor);
}
void XO::playGameGUI_pvp() {
   const int startX = 490, startY = 210,cell_size=100;
    bool game_over = false;
    bool p1_turn = true;
    string msg=" ";
    while (!WindowShouldClose()) {
        //input
        if (!game_over and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
    // cel check
            int col = (mouse_pos.x-startX)/cell_size ;
            int row = (mouse_pos.y-startY)/cell_size;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            //validation
                board[row][col] = p1_turn ? player1.getSymbol() : player2.getSymbol();
               //check win
if (checkWin(player1.getSymbol())) {
    game_over = true;
    msg =  player1.getName() + " wins!" ;
player1.incrementScore();
}
else if (checkWin(player2.getSymbol())) {
    game_over = true;
    msg = player2.getName() + " wins!";
    player2.incrementScore();
}
                //draw
else if (checkDraw()) {
    game_over = true;
    msg = "It's a draw!";
}else {
    p1_turn = !p1_turn;
//p2 turn
}
            }
        }
        // Drawing begins
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        drawBoard();
        // put x and o on board
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        int x = startX + j * cell_size + 30;
        int y = startY + i * cell_size + 30;
        if (board[i][j] == 'X') {
            DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
        }
        else if (board[i][j] == 'O'){
            DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
    }
    }
}
        if (game_over) {
            DrawText(msg.c_str(),500,150,30,YELLOW);
        }
        EndDrawing();
    }
}
void XO::playGameGUI_ai_easy() {
int startX = 490, startY = 210,cell_size=100;
        bool game_over=false;
        string msg=" ";
         srand(time(nullptr));
bool p1_turn=(player1.getSymbol()=='X');
   //ai first if p1!=x
    if (!p1_turn) {
        int ai_row, ai_col;
        // random generator
        do {
            ai_row = rand() % 3;
            ai_col = rand() % 3;
        } while (board[ai_row][ai_col] != ' ');
        board[ai_row][ai_col] = player2.getSymbol();
        p1_turn = true;
    }
    while (!WindowShouldClose()) {
        if (!game_over and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            const int col = (mouse_pos.x - startX) / cell_size;
            const int row = (mouse_pos.y - startY) / cell_size;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] =  player1.getSymbol() ;
                p1_turn = false;
                if (checkWin(player1.getSymbol())) {
                    game_over = true;
                    msg =player1.getName() +" wins!" ;
                    player1.incrementScore();
                }
                else if (checkDraw()) {
                    game_over = true;
                    msg = "It's a draw!";
                }else {
                    int ai_row, ai_col;
                    do {
                        ai_row = rand() % 3;
                        ai_col = rand() % 3;
                    } while (board[ai_row][ai_col] != ' ');
                    board[ai_row][ai_col] = player2.getSymbol();
                    p1_turn = true;
                    if (checkWin(player2.getSymbol())) {
                        game_over = true;
                        msg ="ai wins!";
                        player2.incrementScore();
                    }
                    else if (checkDraw()) {
                        game_over = true;
                        msg = "It's a draw!";
                    }
                }
            }
        }
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        drawBoard();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = startX + j * cell_size + 30;
                int y = startY + i * cell_size + 30;
                if (board[i][j] == 'X')
                    DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
                else if (board[i][j] == 'O')
                    DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
            }
        }
        if (game_over) {
            DrawText(msg.c_str(), 500, 150, 30, YELLOW);
        }
        EndDrawing();
    }
}
void XO::playGameGUI_ai_hard() {
int startX = 490, startY = 210,cell_size=100;
        bool game_over=false;
    bool p1_turn=(player1.getSymbol()=='X');
    string msg=" ";
        if (!p1_turn) {
            bestMove();
            p1_turn = true;
        }
    while (!WindowShouldClose()) {
        if (!game_over and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            const int col = (mouse_pos.x - startX) / cell_size;
            const int row = (mouse_pos.y - startY) / cell_size;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                //p1 turn
                board[row][col] = player1.getSymbol();
                p1_turn = false;
                if (checkWin(player1.getSymbol())) {
                    game_over = true;
                    msg = player1.getName() + " wins!";
                    player1.incrementScore();
                }
                else if (checkDraw()) {
                    game_over = true;
                    msg = "It's a draw!";
                }else {
                    //ai turn
                    bestMove();
                    if (checkWin(player2.getSymbol())) {
                        game_over = true;
                        msg = "ai wins!";
                        player2.incrementScore();
                    }
                    else if (checkDraw()) {
                        game_over = true;
                        msg = "It's a draw!";
                    }
                }
            }
        }
    BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    drawBoard();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = startX + j * cell_size + 30;
            int y = startY + i * cell_size + 30;
            if (board[i][j] == 'X')
                DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
            else if (board[i][j] == 'O')
                DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
        }
    }
        if (game_over) {
            DrawText(msg.c_str(), 500, 150, 30, YELLOW);
        }
        EndDrawing();
    }
}