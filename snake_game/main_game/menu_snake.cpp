#include <snake_game/main_game/menu_snake.h>
#include <string>
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;
int showmenu_snake() {
    BeginDrawing(); EndDrawing();
    Rectangle defualt_btn={490,250,300,60};
    Rectangle lvl_btn={490,350,300,60};
    Rectangle exit_btn={490,450,300,60};
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mousePos,defualt_btn))
                return 1;
            if (CheckCollisionPointRec(mousePos,lvl_btn))
                return 2;
            if (CheckCollisionPointRec(mousePos,exit_btn))
                return 0;
        }

        BeginDrawing();
         ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
         DrawText("Snake Game",520,140,40,WHITE);
         DrawRectangleRec(defualt_btn,DARKBLUE);
         int pvpW = MeasureText("Free for all mode", 25);
         //DrawText("Free for all mode", 520 + (300 - pvpW) / 2, 260, 25, WHITE);
         DrawText("Free for all mode",
                      defualt_btn.x + (defualt_btn.width - pvpW) / 2,
                      defualt_btn.y + (defualt_btn.height - 25) / 2, 25, WHITE);
         DrawRectangleRec(lvl_btn,DARKBLUE);
         int lvlW = MeasureText("Level based mode", 25);
         DrawText("Level based mode",
                      lvl_btn.x + (lvl_btn.width - lvlW) / 2,
                      lvl_btn.y + (lvl_btn.height - 25) / 2, 25, WHITE);
         DrawRectangleRec(exit_btn,DARKBLUE);
         int exW = MeasureText("Exit", 25);
         DrawText("Exit",
                      exit_btn.x + (exit_btn.width - exW) / 2,
                      exit_btn.y + (exit_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}
bool getPlayerName_snake(Snake &snake, const std::string& prompt) {
    std::string name="";
    Rectangle back_btn={490,450,300,60};
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        int key=GetCharPressed();
        if(IsKeyPressed(KEY_ENTER) and !name.empty()){
            snake.setName(name);
            // signal success to caller
            return true;
        }
        if(IsKeyPressed(KEY_ESCAPE)) return false;
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if(CheckCollisionPointRec(mouse_pos, back_btn)) {
                // consume the input for one frame so the main menu does not
                // immediately receive the same mouse release (which shares
                // the same button/position) and inadvertently act on it.
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        if(IsKeyPressed(KEY_BACKSPACE) and !name.empty()){
            name.pop_back();
        }
        if(key >= 32 && key <= 125) name += (char)key;
         BeginDrawing();
         ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText((prompt+" Enter Your Name:").c_str(), 400, 280, 25, WHITE);
         DrawText(name.c_str(), 400, 320, 25, WHITE);
         DrawText("Press Enter to Continue", 400, 380, 20, WHITE);
         // draw the Back button
         DrawRectangleRec(back_btn, DARKBLUE);
         int backW = MeasureText("Back", 25);
         DrawText("Back",
                  back_btn.x + (back_btn.width - backW) / 2,
                  back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    // window closed without confirming -> treat as cancel
    return false;

    }
bool getPlayerColor_snake(Snake &snake, std::string prompt) {
    // four color option buttons and a Back button
    Rectangle green_btn = {260, 300, 150, 60};
    Rectangle red_btn   = {440, 300, 150, 60};
    Rectangle blue_btn  = {620, 300, 150, 60};
    Rectangle dark_btn  = {800, 300, 150, 60};
    Rectangle back_btn  = {490, 450, 300, 60};

    int selected = -1; // no color initially selected

    // wait one frame to clear previous input state
    BeginDrawing();
    EndDrawing();

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        // handle keyboard input
        if (IsKeyPressed(KEY_ESCAPE)) {
            return false; // ESC -> return to main menu
        }

        // number keys 1-4 to select colors
        if (IsKeyPressed(KEY_ONE)) {
            snake.setSymbol('g');
            return true;
        }
        if (IsKeyPressed(KEY_TWO)) {
            snake.setSymbol('r');
            return true;
        }
        if (IsKeyPressed(KEY_THREE)) {
            snake.setSymbol('b');
            return true;
        }
        if (IsKeyPressed(KEY_FOUR)) {
            snake.setSymbol('d');
            return true;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, green_btn)) {
                snake.setSymbol('g');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, red_btn)) {
                snake.setSymbol('r');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, blue_btn)) {
                snake.setSymbol('b');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, dark_btn)) {
                // use a symbol that isn't 'r','g' or 'b' so draw() falls back to DARKGREEN
                snake.setSymbol('d');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, back_btn)) {
                BeginDrawing(); EndDrawing();
                return false;
            }
        }

        // track which button mouse is over for visual feedback
        Vector2 mouse_pos = GetMousePosition();
        selected = -1;
        if (CheckCollisionPointRec(mouse_pos, green_btn)) selected = 0;
        else if (CheckCollisionPointRec(mouse_pos, red_btn)) selected = 1;
        else if (CheckCollisionPointRec(mouse_pos, blue_btn)) selected = 2;
        else if (CheckCollisionPointRec(mouse_pos, dark_btn)) selected = 3;

        BeginDrawing();
        ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText((prompt + " Choose Your Color:").c_str(), 420, 220, 25, WHITE);
        DrawText("(or press 1-4, or ESC to go back)", 420, 250, 18, GRAY);

        DrawRectangleRec(green_btn, selected == 0 ? Color{50, 150, 200, 255} : DARKBLUE);
        int gW = MeasureText("GREEN", 30);
        DrawText("GREEN",
                 green_btn.x + (green_btn.width - gW) / 2,
                 green_btn.y + (green_btn.height - 30) / 2, 30, GREEN);

        DrawRectangleRec(red_btn, selected == 1 ? Color{50, 150, 200, 255} : DARKBLUE);
        int rW = MeasureText("RED", 30);
        DrawText("RED",
                 red_btn.x + (red_btn.width - rW) / 2,
                 red_btn.y + (red_btn.height - 30) / 2, 30, RED);

        DrawRectangleRec(blue_btn, selected == 2 ? Color{50, 150, 200, 255} : DARKBLUE);
        int bW = MeasureText("BLUE", 30);
        DrawText("BLUE",
                 blue_btn.x + (blue_btn.width - bW) / 2,
                 blue_btn.y + (blue_btn.height - 30) / 2, 30, BLUE);

        DrawRectangleRec(dark_btn, selected == 3 ? Color{50, 150, 200, 255} : DARKBLUE);
        int dW = MeasureText("DARKGREEN", 24);
        DrawText("DARKGREEN",
                 dark_btn.x + (dark_btn.width - dW) / 2,
                 dark_btn.y + (dark_btn.height - 24) / 2, 24, DARKGREEN);

        // Back button
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("Back", 25);
        DrawText("Back",
                 back_btn.x + (back_btn.width - backW) / 2,
                 back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}
int showPostGame_menu(bool won, bool levelComplete, int level,const std::map<std::string, int>& board) {

    Rectangle play_btn = {WINDOW_WIDTH/2 - 160, WINDOW_HEIGHT/2 + 120, 140, 50};
    Rectangle menu_btn = {WINDOW_WIDTH/2 + 20,  WINDOW_HEIGHT/2 + 120, 140, 50};

    // sort leaderboard descending
    std::vector<std::pair<std::string, int>> entries(board.begin(), board.end());
    std::sort(entries.begin(), entries.end(),
        [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) {
            return b.second < a.second;
        });

    BeginDrawing(); EndDrawing(); // consume one frame

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(m, play_btn)) return 1; // play again
            if (CheckCollisionPointRec(m, menu_btn)) return 0; // main menu
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        // result
        if (levelComplete && level == 3) {
            int w = MeasureText("You Beat All Levels!", 35);
            DrawText("You Beat All Levels!", WINDOW_WIDTH/2 - w/2, 80, 35, GOLD);

            // leaderboard
            DrawText("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                DrawText(line, WINDOW_WIDTH/2 - lw/2, 200 + i * 30, 20, WHITE);
            }

            // only show Main Menu button for level 3 completion
            DrawRectangleRec(menu_btn, DARKBLUE);
            int mmW = MeasureText("Main Menu", 20);
            DrawText("Main Menu",
                menu_btn.x + (menu_btn.width - mmW)/2,
                menu_btn.y + (menu_btn.height - 20)/2, 20, WHITE);
        } else if (levelComplete) {
            // Level complete but not final level
            int w = MeasureText("Level Complete!", 40);
            DrawText("Level Complete!", WINDOW_WIDTH/2 - w/2, 80, 40, GOLD);

            // leaderboard
            DrawText("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                DrawText(line, WINDOW_WIDTH/2 - lw/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            DrawRectangleRec(play_btn, DARKBLUE);
            int pwW = MeasureText("Next Level", 20);
            DrawText("Next Level",
                play_btn.x + (play_btn.width - pwW)/2,
                play_btn.y + (play_btn.height - 20)/2, 20, WHITE);

            DrawRectangleRec(menu_btn, DARKBLUE);
            int mmW = MeasureText("Main Menu", 20);
            DrawText("Main Menu",
                menu_btn.x + (menu_btn.width - mmW)/2,
                menu_btn.y + (menu_btn.height - 20)/2, 20, WHITE);
        } else if (won) {
            int w = MeasureText("You Win!", 40);
            DrawText("You Win!", WINDOW_WIDTH/2 - w/2, 80, 40, GOLD);

            // leaderboard
            DrawText("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                DrawText(line, WINDOW_WIDTH/2 - lw/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            DrawRectangleRec(play_btn, DARKBLUE);
            int pwW = MeasureText("Play Again", 20);
            DrawText("Play Again",
                play_btn.x + (play_btn.width - pwW)/2,
                play_btn.y + (play_btn.height - 20)/2, 20, WHITE);

            DrawRectangleRec(menu_btn, DARKBLUE);
            int mmW = MeasureText("Main Menu", 20);
            DrawText("Main Menu",
                menu_btn.x + (menu_btn.width - mmW)/2,
                menu_btn.y + (menu_btn.height - 20)/2, 20, WHITE);
        } else {
            // Game Over
            int w = MeasureText("Game Over", 40);
            DrawText("Game Over", WINDOW_WIDTH/2 - w/2, 80, 40, RED);

            // leaderboard
            DrawText("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                DrawText(line, WINDOW_WIDTH/2 - lw/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            DrawRectangleRec(play_btn, DARKBLUE);
            int pwW = MeasureText("Play Again", 20);
            DrawText("Play Again",
                play_btn.x + (play_btn.width - pwW)/2,
                play_btn.y + (play_btn.height - 20)/2, 20, WHITE);

            DrawRectangleRec(menu_btn, DARKBLUE);
            int mmW = MeasureText("Main Menu", 20);
            DrawText("Main Menu",
                menu_btn.x + (menu_btn.width - mmW)/2,
                menu_btn.y + (menu_btn.height - 20)/2, 20, WHITE);
        }
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}