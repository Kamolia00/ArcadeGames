#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "ui/button_helpers.h"
extern bool mutedBGm;
extern Music bgm;

bool mutedSFX = false;

extern Rectangle sfx_btn;
extern Rectangle mute_btn;
using namespace std;
namespace {
constexpr double kAiTurnDelaySeconds = 1.0;

void startAiTurnDelay(bool &aiWaiting, double &aiMoveTime) {
    aiMoveTime = GetTime() + kAiTurnDelaySeconds;
    aiWaiting = true;
}
}
//const
XO::XO(Player &p1, Player &p2) : player1(p1), player2(p2) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    clickSfx = LoadSound("assets/sounds/xo.ogg");
}
XO::~XO() {
    UnloadSound(clickSfx);
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
    Rectangle continue_btn = {490, 550, 300, 60};
    double gameOverTime = 0;
   const int startX = 490, startY = 210,cell_size=100;
    int kamoliaMovesP1 = 0;
    int kamoliaMovesP2 = 0;
    bool game_over = false;
    // X always starts:
    bool p1_turn = (player1.getSymbol() == 'X');
    string msg=" ";
while (!WindowShouldClose()) {
    UpdateMusicStream(bgm);
    if (mutedBGm) PauseMusicStream(bgm);
    else ResumeMusicStream(bgm);

    // --- input ---
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, sfx_btn)) mutedSFX = !mutedSFX;
        if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;

        // continue button — only after 0.3s delay
        if (game_over && (GetTime() - gameOverTime > 0.3)) {
            if (CheckCollisionPointRec(mouse_pos, continue_btn)) break;
        }
    }

    if (!game_over && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();
        // cell check
        int col = (mouse_pos.x - startX) / cell_size;
        int row = (mouse_pos.y - startY) / cell_size;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = p1_turn ? player1.getSymbol() : player2.getSymbol();
            if (!mutedSFX) PlaySound(clickSfx);

            if (p1_turn && player1.getName() == "kamolia") kamoliaMovesP1++;
            if (!p1_turn && player2.getName() == "kamolia") kamoliaMovesP2++;

            Player &cur = p1_turn ? player1 : player2;
            int &kamoliaCount = p1_turn ? kamoliaMovesP1 : kamoliaMovesP2;

            if (cur.getName() == "kamolia" && kamoliaCount >= 3) {
                game_over = true;
                gameOverTime = GetTime();
                msg = "kamolia wins! (obviously!)";
                cur.incrementScore();
            } else if (checkWin(player1.getSymbol())) {
                game_over = true;
                gameOverTime = GetTime();
                msg = player1.getName() + " wins!";
                player1.incrementScore();
            } else if (checkWin(player2.getSymbol())) {
                game_over = true;
                gameOverTime = GetTime();
                msg = player2.getName() + " wins!";
                player2.incrementScore();
            } else if (checkDraw()) {
                game_over = true;
                gameOverTime = GetTime();
                msg = "It's a draw!";
            } else {
                p1_turn = !p1_turn;
            }
        }
    }

    // --- draw ---
    BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    drawBoard();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = startX + j * cell_size + 35;
            int y = startY + i * cell_size + 35;
            if (board[i][j] == 'X')
                DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
            else if (board[i][j] == 'O')
                DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
        }
    }

    if (game_over) {
        DrawText(msg.c_str(), 500, 150, 30, YELLOW);

        menu_ui::DrawMenuButton(continue_btn,"Continue",25);

        // win cells highlight
        int cells[3][2];
        char winSym = checkWin(player1.getSymbol()) ? player1.getSymbol() : player2.getSymbol();
        if (GetWinCells(winSym, cells)) {
            for (int k = 0; k < 3; k++) {
                int x = startX + cells[k][1] * cell_size;
                int y = startY + cells[k][0] * cell_size;
                DrawRectangle(x, y, cell_size, cell_size, {255, 215, 0, 80});
            }
        }
    } else {
        string turn = p1_turn ? player1.getName() + "'s turn" : player2.getName() + "'s turn";
        DrawText(turn.c_str(), 490, 150, 25, WHITE);
    }

    menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
    menu_ui::DrawMenuButton(sfx_btn,mutedSFX?"SFX ON": "SFX OFF",20, mutedBGm ? GREEN : RED);
    EndDrawing();
}
}
void XO::playGameGUI_ai_easy() {
Rectangle continue_btn = {490, 550, 300, 60};
double gameOverTime = 0;
const int startX = 490, startY = 210, cell_size = 100;
bool game_over = false;
bool p1_turn = (player1.getSymbol() == 'X');
string msg = " ";
srand(time(nullptr));

bool openingDelayActive = true;
double openingMoveTime = GetTime() + kAiTurnDelaySeconds;
bool aiWaiting = false;
double aiMoveTime = 0.0;

BeginDrawing(); EndDrawing();

while (!WindowShouldClose()) {
    UpdateMusicStream(bgm);
    if (mutedBGm) PauseMusicStream(bgm);
    else ResumeMusicStream(bgm);

    // opening AI move
    if (openingDelayActive && GetTime() >= openingMoveTime) {
        if (!p1_turn) {
            int r, c;
            do { r = rand() % 3; c = rand() % 3; } while (board[r][c] != ' ');
            board[r][c] = player2.getSymbol();
            if (!mutedSFX) PlaySound(clickSfx);
            if (checkWin(player2.getSymbol())) {
                game_over = true; gameOverTime = GetTime();
                msg = "AI wins!"; player2.incrementScore();
            } else if (checkDraw()) {
                game_over = true; gameOverTime = GetTime();
                msg = "It's a draw!";
            } else {
                p1_turn = true;
            }
        }
        openingDelayActive = false;
    }

    // AI delay move
    if (!openingDelayActive && !game_over && !p1_turn) {
        if (!aiWaiting) startAiTurnDelay(aiWaiting, aiMoveTime);
        if (aiWaiting && GetTime() >= aiMoveTime) {
            aiWaiting = false;
            int r, c;
            do { r = rand() % 3; c = rand() % 3; } while (board[r][c] != ' ');
            board[r][c] = player2.getSymbol();
            if (!mutedSFX) PlaySound(clickSfx);
            if (checkWin(player2.getSymbol())) {
                game_over = true; gameOverTime = GetTime();
                msg = "AI wins!"; player2.incrementScore();
            } else if (checkDraw()) {
                game_over = true; gameOverTime = GetTime();
                msg = "It's a draw!";
            } else {
                p1_turn = true;
            }
        }
    }

    // input
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();

        if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
        if (CheckCollisionPointRec(mouse_pos, sfx_btn))  mutedSFX = !mutedSFX;

        // continue button
        if (game_over && (GetTime() - gameOverTime > 0.3)) {
            if (CheckCollisionPointRec(mouse_pos, continue_btn)) break;
        }

        // player move
        if (!openingDelayActive && !game_over && p1_turn) {
            int col = (mouse_pos.x - startX) / cell_size;
            int row = (mouse_pos.y - startY) / cell_size;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] = player1.getSymbol();
                if (!mutedSFX) PlaySound(clickSfx);
                if (checkWin(player1.getSymbol())) {
                    game_over = true; gameOverTime = GetTime();
                    msg = player1.getName() + " wins!"; player1.incrementScore();
                } else if (checkDraw()) {
                    game_over = true; gameOverTime = GetTime();
                    msg = "It's a draw!";
                } else {
                    p1_turn = false; aiWaiting = false;
                }
            }
        }
    }

    // draw
    BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    drawBoard();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = startX + j * cell_size + 30;
            int y = startY + i * cell_size + 30;
            if      (board[i][j] == 'X') DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
            else if (board[i][j] == 'O') DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
        }
    }

    if (game_over) {
        DrawText(msg.c_str(), 500, 150, 30, YELLOW);

        menu_ui::DrawMenuButton(continue_btn,"Continue",25);

        // win highlight
        int cells[3][2];
        char winSym = checkWin(player1.getSymbol()) ? player1.getSymbol() : player2.getSymbol();
        if (GetWinCells(winSym, cells)) {
            for (int k = 0; k < 3; k++) {
                int x = startX + cells[k][1] * cell_size;
                int y = startY + cells[k][0] * cell_size;
                DrawRectangle(x, y, cell_size, cell_size, {255, 215, 0, 80});
            }
        }
    } else {
        DrawText(p1_turn ? "Your turn" : "AI thinking...", 500, 150, 25, WHITE);
    }

    menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
    menu_ui::DrawMenuButton(sfx_btn,mutedSFX?"SFX ON": "SFX OFF",20, mutedBGm ? GREEN : RED);
    EndDrawing();
}
}
void XO::playGameGUI_ai_hard() {
    Rectangle continue_btn = {490, 550, 300, 60};
    double gameOverTime = 0;
    const int startX = 490, startY = 210, cell_size = 100;
    bool game_over = false;
    bool p1_turn = (player1.getSymbol() == 'X');
    string msg = " ";

    bool openingDelayActive = true;
    double openingMoveTime = GetTime() + kAiTurnDelaySeconds;
    bool aiWaiting = false;
    double aiMoveTime = 0.0;

    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        // opening AI move
        if (openingDelayActive && GetTime() >= openingMoveTime) {
            if (!p1_turn) {
                bestMove();
                if (!mutedSFX) PlaySound(clickSfx);
                if (checkWin(player2.getSymbol())) {
                    game_over = true; gameOverTime = GetTime();
                    msg = "AI wins!"; player2.incrementScore();
                } else if (checkDraw()) {
                    game_over = true; gameOverTime = GetTime();
                    msg = "It's a draw!";
                } else {
                    p1_turn = true;
                }
            }
            openingDelayActive = false;
        }

        // AI delay move
        if (!openingDelayActive && !game_over && !p1_turn) {
            if (!aiWaiting) startAiTurnDelay(aiWaiting, aiMoveTime);
            if (aiWaiting && GetTime() >= aiMoveTime) {
                aiWaiting = false;
                bestMove();
                if (!mutedSFX) PlaySound(clickSfx);
                if (checkWin(player2.getSymbol())) {
                    game_over = true; gameOverTime = GetTime();
                    msg = "AI wins!"; player2.incrementScore();
                } else if (checkDraw()) {
                    game_over = true; gameOverTime = GetTime();
                    msg = "It's a draw!";
                } else {
                    p1_turn = true;
                }
            }
        }

        // input
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();

            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, sfx_btn))  mutedSFX = !mutedSFX;

            // continue button
            if (game_over && (GetTime() - gameOverTime > 0.3)) {
                if (CheckCollisionPointRec(mouse_pos, continue_btn)) break;
            }

            // player move
            if (!openingDelayActive && !game_over && p1_turn) {
                int col = (mouse_pos.x - startX) / cell_size;
                int row = (mouse_pos.y - startY) / cell_size;
                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                    board[row][col] = player1.getSymbol();
                    if (!mutedSFX) PlaySound(clickSfx);
                    if (checkWin(player1.getSymbol())) {
                        game_over = true; gameOverTime = GetTime();
                        msg = player1.getName() + " wins!"; player1.incrementScore();
                    } else if (checkDraw()) {
                        game_over = true; gameOverTime = GetTime();
                        msg = "It's a draw!";
                    } else {
                        p1_turn = false; aiWaiting = false;
                    }
                }
            }
        }

        // draw
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        drawBoard();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = startX + j * cell_size + 30;
                int y = startY + i * cell_size + 30;
                if      (board[i][j] == 'X') DrawTextEx(font, "X", {(float)x, (float)y}, 40, 0, RED);
                else if (board[i][j] == 'O') DrawTextEx(font, "O", {(float)x, (float)y}, 40, 0, GREEN);
            }
        }

        if (game_over) {
            DrawText(msg.c_str(), 500, 150, 30, YELLOW);

            menu_ui::DrawMenuButton(continue_btn,"Continue",25);

            int cells[3][2];
            char winSym = checkWin(player1.getSymbol()) ? player1.getSymbol() : player2.getSymbol();
            if (GetWinCells(winSym, cells)) {
                for (int k = 0; k < 3; k++) {
                    int x = startX + cells[k][1] * cell_size;
                    int y = startY + cells[k][0] * cell_size;
                    DrawRectangle(x, y, cell_size, cell_size, {255, 215, 0, 80});
                }
            }
        } else {
            DrawText(p1_turn ? "Your turn" : "AI thinking...", 500, 150, 25, WHITE);
        }

        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        menu_ui::DrawMenuButton(sfx_btn,mutedSFX?"SFX ON": "SFX OFF",20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
}
bool XO::GetWinCells(char Symbol,int cells[3][2]){
    //rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==Symbol && board[i][1]==Symbol && board[i][2]==Symbol) {
            cells[0][0]=i; cells[0][1]=0;
            cells[1][0]=i; cells[1][1]=1;
            cells[2][0]=i; cells[2][1]=2;
            return true;
        }
    }
    //columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j]==Symbol && board[1][j]==Symbol && board[2][j]==Symbol) {
            cells[0][0]=0; cells[0][1]=j;
            cells[1][0]=1; cells[1][1]=j;
            cells[2][0]=2; cells[2][1]=j;
            return true;
        }
    }
    //diagonals
    // main
    if (board[0][0]==Symbol && board[1][1]==Symbol && board[2][2]==Symbol) {
        cells[0][0]=0; cells[0][1]=0;
        cells[1][0]=1; cells[1][1]=1;
        cells[2][0]=2; cells[2][1]=2;
        return true;
    }
    //sup
    if (board[0][2]==Symbol && board[1][1]==Symbol && board[2][0]==Symbol) {
        cells[0][0]=0; cells[0][1]=2;
        cells[1][0]=1; cells[1][1]=1;
        cells[2][0]=2; cells[2][1]=0;
        return true;
    }
    return false;
}