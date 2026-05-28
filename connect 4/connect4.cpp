#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
//const
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
void connect4::draw_board(){
    // consts
    int startX = 342, startY =100;
    int cellSize = 85;
    int cols = 7, rows = 7;
    int gridWidth = cellSize * cols;
    int gridHeight = cellSize * rows;
    Color lineColor = {100, 200, 255, 255};
    int thickness = 2;

    // border
    DrawLineEx({(float)startX, (float)startY}, {(float)(startX + gridWidth), (float)startY}, thickness, lineColor);
    DrawLineEx({(float)startX, (float)(startY + gridHeight)}, {(float)(startX + gridWidth), (float)(startY + gridHeight)}, thickness, lineColor);
    DrawLineEx({(float)startX, (float)startY}, {(float)startX, (float)(startY + gridHeight)}, thickness, lineColor);
    DrawLineEx({(float)(startX + gridWidth), (float)startY}, {(float)(startX + gridWidth), (float)(startY + gridHeight)}, thickness, lineColor);

    // vertical inner lines
    for (int j = 1; j < cols; j++)
        DrawLineEx({(float)(startX + j * cellSize), (float)startY}, {(float)(startX + j * cellSize), (float)(startY + gridHeight)}, thickness, lineColor);

    // horizontal inner lines
    for (int i = 1; i < rows; i++)
        DrawLineEx({(float)startX, (float)(startY + i * cellSize)}, {(float)(startX + gridWidth), (float)(startY + i * cellSize)}, thickness, lineColor);

    // circles and colors
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int cx = startX + j * cellSize + cellSize / 2;
            int cy = startY + i * cellSize + cellSize / 2;
            int radius = 30;

            if (board[i][j] == 'X')
                DrawCircle(cx, cy, radius, RED);
            else if (board[i][j] == 'O')
                DrawCircle(cx, cy, radius, YELLOW);
            else
                DrawCircle(cx, cy, radius, {20, 20, 40, 255});
        }
    }
}
void connect4::pvp_gui() {
    bool game_over = false;
    bool p1_turn = (p1.getSymbol() == 'X');
    const int startX = 342, startY = 100, cell_size = 85;
    const int gridHeight = cell_size * 7;
    string msg = " ";

    // animation
    bool  animating    = false;
    float animY        = 0.0f;
    float animTargetY  = 0.0f;
    int   animCol      = 0;
    int   animTargetRow= 0;
    char  animSymbol   = ' ';
    const float animSpeed = 900.0f;

    // wasta cases
    int kamoliaMovesP1 = 0;
    int kamoliaMovesP2 = 0;

    while (!WindowShouldClose()) {

        //  input
        if (!game_over && !animating && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            const int col = (mouse_pos.x - startX) / cell_size;
            if (col >= 0 && col < 7 && board[0][col] == ' ') {
                for (int i = 6; i >= 0; i--) {
                    if (board[i][col] == ' ') {
                        animTargetRow = i; break;
                    }
                }
                // animation of each move
                animCol     = col;
                animSymbol  = p1_turn ? p1.getSymbol() : p2.getSymbol();
                animY       = startY + cell_size / 2.0f;
                animTargetY = startY + animTargetRow * cell_size + cell_size / 2.0f;
                animating   = true;

                // track kamolia moves before animation commits
                if (p1_turn && p1.getName() == "kamolia") kamoliaMovesP1++;
                if (!p1_turn && p2.getName() == "kamolia") kamoliaMovesP2++;
            }
        }

        //  animation update
        if (animating) {
            animY += animSpeed * GetFrameTime();
            if (animY >= animTargetY) {
                animY     = animTargetY;
                animating = false;
                board[animTargetRow][animCol] = animSymbol;

                bool wasP1 = (animSymbol == p1.getSymbol());
                Player &cur = wasP1 ? p1 : p2;
                int &kamoliaCount = wasP1 ? kamoliaMovesP1 : kamoliaMovesP2;

                // wasta case
                if (cur.getName() == "kamolia" && kamoliaCount >= 4) {
                    game_over = true;
                    msg = "kamolia wins! (obviously)";
                    cur.incrementScore();
                }
                else if (check_win(cur.getSymbol())) {
                    game_over = true;
                    msg = cur.getName() + " wins!";
                    cur.incrementScore();
                }
                else if (check_draw()) {
                    game_over = true;
                    msg = "It's a draw!";
                }
                else {
                    p1_turn = !p1_turn;
                }
            }
        }

        //  drawing 
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        Vector2 mouse_pos = GetMousePosition();
        const int hover_col = (mouse_pos.x - startX) / cell_size;
        if (!game_over && !animating && hover_col >= 0 && hover_col < 7)
            DrawRectangle(startX + hover_col * cell_size, startY, cell_size, gridHeight, {100, 200, 255, 50});
        draw_board();

        // falling piece
        if (animating) {
            Color c = (animSymbol == 'X') ? RED : (Color){255, 200, 0, 255};
            DrawCircle(startX + animCol * cell_size + cell_size / 2, (int)animY, 30, c);
        }

        if (game_over) {
            DrawText(msg.c_str(), startX, startY - 70, 25, YELLOW);
            DrawText("Press Enter to continue", startX, startY - 45, 20, DARKGRAY);
        } else {
            string turn = p1_turn ? p1.getName() + "'s turn" : p2.getName() + "'s turn";
            DrawText(turn.c_str(), startX, startY - 40, 25, WHITE);
        }
        EndDrawing();
        if (game_over && IsKeyPressed(KEY_ENTER)) break;
    }
}
void connect4::ai_ez_gui() {
    bool game_over = false;
    bool p1_turn = p1.getSymbol() == 'X';
    const int startX = 342, startY = 100, cell_size = 85;
    const int gridHeight = cell_size * 7;
    string msg = " ";

    // animation
    bool animating   = false;
    float animY      = 0.0f;
    float animTargetY= 0.0f;
    int   animCol    = 0;
    int   animTargetRow = 0;
    char  animSymbol = ' ';
    const float animSpeed = 800.0f;

    // AI delay
    bool   aiWaiting  = false;
    double aiMoveTime = 0.0;

    while (!WindowShouldClose()) {

        // player input move
        if (!game_over && p1_turn && !animating && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            const int col = (mouse_pos.x - startX) / cell_size;
            if (col >= 0 && col < 7 && board[0][col] == ' ') {
                for (int i = 6; i >= 0; i--) {
                    if (board[i][col] == ' ') {
                        animTargetRow = i; break;
                    }
                }
                animCol     = col;
                animSymbol  = p1.getSymbol();
                animY       = startY + cell_size / 2.0f;
                animTargetY = startY + animTargetRow * cell_size + cell_size / 2.0f;
                animating   = true;
            }
        }

        // AI delay
        if (!game_over && !p1_turn && !animating) {
            if (!aiWaiting) {
                aiMoveTime = GetTime() + 1.5;
                aiWaiting  = true;
            }
            if (aiWaiting && GetTime() >= aiMoveTime) {
                aiWaiting = false;
                int col;
                do { col = rand() % 7; } while (board[0][col] != ' ');
                for (int i = 6; i >= 0; i--) {
                    if (board[i][col] == ' ') {
                        animTargetRow = i; break;
                    }
                }
                animCol     = col;
                animSymbol  = p2.getSymbol();
                animY       = startY + cell_size / 2.0f;
                animTargetY = startY + animTargetRow * cell_size + cell_size / 2.0f;
                animating   = true;
            }
        }

        // animation update
        if (animating) {
            animY += animSpeed * GetFrameTime();
            if (animY >= animTargetY) {
                animY     = animTargetY;
                animating = false;
                board[animTargetRow][animCol] = animSymbol;

                bool wasP1 = (animSymbol == p1.getSymbol());
                if (wasP1) {
                    if      (check_win(p1.getSymbol())) {
                        game_over=true; msg=p1.getName()+" wins!"; p1.incrementScore();
                    }
                    else if (check_draw()) {
                        game_over=true; msg="It's a draw!";
                    }
                    else {
                        p1_turn=false;
                    }
                } else {
                    if      (check_win(p2.getSymbol())) {
                        game_over=true; msg=p2.getName()+" wins!"; p2.incrementScore();
                    }
                    else if (check_draw()) {
                        game_over=true; msg="It's a draw!";
                    }
                    else {
                        p1_turn=true;
                    }
                }
            }
        }

        // drawing
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        Vector2 mouse_pos = GetMousePosition();
        const int hover_col = (mouse_pos.x - startX) / cell_size;
        if (!game_over && p1_turn && !animating && hover_col >= 0 && hover_col < 7)
            DrawRectangle(startX + hover_col * cell_size, startY, cell_size, gridHeight, {100, 200, 255, 50});
        draw_board();

        // falling piece
        if (animating) {
            Color c = (animSymbol == 'X') ? RED : (Color){255, 200, 0, 255};
            DrawCircle(startX + animCol * cell_size + cell_size / 2, (int)animY, 30, c);
        }

        if (game_over) {
            DrawText(msg.c_str(), startX, startY - 70, 25, YELLOW);
            DrawText("Press Enter to continue", startX, startY - 45, 20, DARKGRAY);
        } else {
            string turn = p1_turn ? p1.getName() + "'s turn" : "AI thinking...";
            DrawText(turn.c_str(), startX, startY - 40, 25, WHITE);
        }
        EndDrawing();
        if (game_over && IsKeyPressed(KEY_ENTER)) break;
    }
}
void connect4::ai_hard_gui() {
    bool game_over = false;
    bool p1_turn = p1.getSymbol() == 'X';
    const int startX = 342, startY = 100, cell_size = 85;
    const int gridHeight = cell_size * 7;
    string msg = " ";

    // animation
    bool animating   = false;
    float animY      = 0.0f;
    float animTargetY= 0.0f;
    int   animCol    = 0;
    int   animTargetRow = 0;
    char  animSymbol = ' ';
    const float animSpeed = 800.0f;

    // AI delay
    bool   aiWaiting  = false;
    double aiMoveTime = 0.0;

    while (!WindowShouldClose()) {

        // --- player input ---
        if (!game_over && p1_turn && !animating && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            const int col = (mouse_pos.x - startX) / cell_size;
            if (col >= 0 && col < 7 && board[0][col] == ' ') {
                for (int i = 6; i >= 0; i--) {
                    if (board[i][col] == ' ') { animTargetRow = i; break; }
                }
                animCol     = col;
                animSymbol  = p1.getSymbol();
                animY       = startY + cell_size / 2.0f;
                animTargetY = startY + animTargetRow * cell_size + cell_size / 2.0f;
                animating   = true;
            }
        }

        // --- AI delay scheduling ---
        if (!game_over && !p1_turn && !animating) {
            if (!aiWaiting) {
                aiMoveTime = GetTime() + 1.5;
                aiWaiting  = true;
            }
            if (aiWaiting && GetTime() >= aiMoveTime) {
                aiWaiting = false;
                int col = getBestMove(9);
                for (int i = 6; i >= 0; i--) {
                    if (board[i][col] == ' ') { animTargetRow = i; break; }
                }
                animCol     = col;
                animSymbol  = p2.getSymbol();
                animY       = startY + cell_size / 2.0f;
                animTargetY = startY + animTargetRow * cell_size + cell_size / 2.0f;
                animating   = true;
            }
        }

        // --- animation update ---
        if (animating) {
            animY += animSpeed * GetFrameTime();
            if (animY >= animTargetY) {
                animY     = animTargetY;
                animating = false;
                board[animTargetRow][animCol] = animSymbol;

                bool wasP1 = (animSymbol == p1.getSymbol());
                if (wasP1) {
                    if      (check_win(p1.getSymbol())) { game_over=true; msg=p1.getName()+" wins!"; p1.incrementScore(); }
                    else if (check_draw())               { game_over=true; msg="It's a draw!"; }
                    else                                 { p1_turn=false; }
                } else {
                    if      (check_win(p2.getSymbol())) { game_over=true; msg=p2.getName()+" wins!"; p2.incrementScore(); }
                    else if (check_draw())               { game_over=true; msg="It's a draw!"; }
                    else                                 { p1_turn=true; }
                }
            }
        }

        // --- drawing ---
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        Vector2 mouse_pos = GetMousePosition();
        const int hover_col = (mouse_pos.x - startX) / cell_size;
        if (!game_over && p1_turn && !animating && hover_col >= 0 && hover_col < 7)
            DrawRectangle(startX + hover_col * cell_size, startY, cell_size, gridHeight, {100, 200, 255, 50});
        draw_board();

        // falling piece
        if (animating) {
            Color c = (animSymbol == 'X') ? RED : (Color){255, 200, 0, 255};
            DrawCircle(startX + animCol * cell_size + cell_size / 2, (int)animY, 30, c);
        }

        if (game_over) {
            DrawText(msg.c_str(), startX, startY - 70, 25, YELLOW);
            DrawText("Press Enter to continue", startX, startY - 45, 20, DARKGRAY);
        } else {
            string turn = p1_turn ? p1.getName() + "'s turn" : "AI thinking...";
            DrawText(turn.c_str(), startX, startY - 40, 25, WHITE);
        }
        EndDrawing();
        if (game_over && IsKeyPressed(KEY_ENTER)) break;
    }
}
