#include <snake_game/main_game/menu_snake.h>
#include <string>
#include "ui/button_helpers.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern Rectangle sfx_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;
int showmenu_snake() {
    BeginDrawing(); EndDrawing();
    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle defualt_btn = menu_ui::ReferenceRect(490, 250, 300, 60);
        Rectangle lvl_btn = menu_ui::ReferenceRect(490, 350, 300, 60);
        Rectangle back_btn = menu_ui::ReferenceRect(490, 450, 300, 60);
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
            if (CheckCollisionPointRec(mousePos,back_btn))
                return 0;
        }

        BeginDrawing();
         ClearBackground({20,20,40,225});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
         menu_ui::DrawTextRef("Snake Game", 520, 140, 40, WHITE);
         menu_ui::DrawMenuButton(defualt_btn, "Free for all mode", 25);
         menu_ui::DrawMenuButton(lvl_btn, "Level based mode", 25);
         menu_ui::DrawMenuButton(back_btn, "Back", 25);
         menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}
bool getPlayerName_snake(Snake &snake, const std::string& prompt) {
    std::string name="";

    BeginDrawing();
    EndDrawing();
#ifdef PLATFORM_WEB
    g_webName.clear();
    EM_ASM({ showNameKeyboard(); });
#endif
    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle back_btn = menu_ui::ReferenceRect(490, 510, 300, 60);
        Rectangle cont_btn = menu_ui::ReferenceRect(490, 400, 300, 60);
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
#ifdef PLATFORM_WEB
        name = g_webName;
#else
        int key=GetCharPressed();
#endif
        if(IsKeyPressed(KEY_ENTER) and !name.empty()){
            snake.setName(name);
            // signal success to caller
#ifdef PLATFORM_WEB
            EM_ASM({ hideNameKeyboard(); });
#endif
            return true;
        }
        if(IsKeyPressed(KEY_ESCAPE)) {
#ifdef PLATFORM_WEB
            EM_ASM({ hideNameKeyboard(); });
#endif
            return false;
        }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if(CheckCollisionPointRec(mouse_pos, back_btn)) {
                // consume the input for one frame so the main menu does not
                // immediately receive the same mouse release (which shares
                // the same button/position) and inadvertently act on it.
                BeginDrawing(); EndDrawing();
#ifdef PLATFORM_WEB
                EM_ASM({ hideNameKeyboard(); });
#endif
                return false;
            }
        }
#ifndef PLATFORM_WEB
        if(IsKeyPressed(KEY_BACKSPACE) and !name.empty()){
            name.pop_back();
        }
#endif
        auto m=GetMousePosition();
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) and CheckCollisionPointRec(m, cont_btn) and !name.empty()){
            snake.setName(name);
            // signal success to caller
#ifdef PLATFORM_WEB
            EM_ASM({ hideNameKeyboard(); });
#endif
            return true;
        }
#ifndef PLATFORM_WEB
        if(key >= 32 && key <= 125) name += (char)key;
#endif
         BeginDrawing();
         ClearBackground({20,20,40,225});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef((prompt+" Enter Your Name:").c_str(), 400, 280, 25, WHITE);
         menu_ui::DrawTextRef(name.c_str(), 400, 320, 25, WHITE);
         // draw the Back button
         menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(cont_btn, "Continue", 25);
         menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    // window closed without confirming -> treat as cancel
#ifdef PLATFORM_WEB
    EM_ASM({ hideNameKeyboard(); });
#endif
    return false;

    }
bool getPlayerColor_snake(Snake &snake, std::string prompt) {
    int selected = -1; // no color initially selected

    // wait one frame to clear previous input state
    BeginDrawing();
    EndDrawing();

    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle green_btn = menu_ui::ReferenceRect(260, 300, 150, 60);
        Rectangle red_btn = menu_ui::ReferenceRect(440, 300, 150, 60);
        Rectangle blue_btn = menu_ui::ReferenceRect(620, 300, 150, 60);
        Rectangle dark_btn = menu_ui::ReferenceRect(800, 300, 150, 60);
        Rectangle back_btn = menu_ui::ReferenceRect(490, 450, 300, 60);
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
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef((prompt + " Choose Your Color:").c_str(), 420, 220, 25, WHITE);
        menu_ui::DrawTextRef("(or press 1-4, or ESC to go back)", 420, 250, 18, GRAY);

        DrawRectangleRec(green_btn, selected == 0 ? Color{50, 150, 200, 255} : DARKBLUE);
        int greenFontSize = menu_ui::ReferenceFontSize(30);
        int gW = MeasureText("GREEN", greenFontSize);
        DrawText("GREEN",
                 green_btn.x + (green_btn.width - gW) / 2,
                 green_btn.y + (green_btn.height - greenFontSize) / 2, greenFontSize, GREEN);

        DrawRectangleRec(red_btn, selected == 1 ? Color{50, 150, 200, 255} : DARKBLUE);
        int redFontSize = menu_ui::ReferenceFontSize(30);
        int rW = MeasureText("RED", redFontSize);
        DrawText("RED",
                 red_btn.x + (red_btn.width - rW) / 2,
                 red_btn.y + (red_btn.height - redFontSize) / 2, redFontSize, RED);

        DrawRectangleRec(blue_btn, selected == 2 ? Color{50, 150, 200, 255} : DARKBLUE);
        int blueFontSize = menu_ui::ReferenceFontSize(30);
        int bW = MeasureText("BLUE", blueFontSize);
        DrawText("BLUE",
                 blue_btn.x + (blue_btn.width - bW) / 2,
                 blue_btn.y + (blue_btn.height - blueFontSize) / 2, blueFontSize, BLUE);

        DrawRectangleRec(dark_btn, selected == 3 ? Color{50, 150, 200, 255} : DARKBLUE);
        int darkFontSize = menu_ui::ReferenceFontSize(24);
        int dW = MeasureText("DARKGREEN", darkFontSize);
        DrawText("DARKGREEN",
                 dark_btn.x + (dark_btn.width - dW) / 2,
                 dark_btn.y + (dark_btn.height - darkFontSize) / 2, darkFontSize, DARKGREEN);

        // Back button
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}
int showPostGame_menu(bool won, bool levelComplete, int level,const std::map<std::string, int>& board) {

    // sort leaderboard descending
    std::vector<std::pair<std::string, int>> entries(board.begin(), board.end());
    std::sort(entries.begin(), entries.end(),
        [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) {
            return b.second < a.second;
        });

    BeginDrawing(); EndDrawing(); // consume one frame

    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle play_btn = menu_ui::ReferenceRect(WINDOW_WIDTH/2 - 160, WINDOW_HEIGHT/2 + 120, 140, 50);
        Rectangle menu_btn = menu_ui::ReferenceRect(WINDOW_WIDTH/2 + 20, WINDOW_HEIGHT/2 + 120, 140, 50);
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
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        // result
        if (levelComplete && level == 3) {
            int w = MeasureText("You Beat All Levels!", 35);
            menu_ui::DrawTextCenteredRef("You Beat All Levels!", WINDOW_WIDTH/2, 80, 35, GOLD);

            // leaderboard
            menu_ui::DrawTextRef("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                menu_ui::DrawTextCenteredRef(line, WINDOW_WIDTH/2, 200 + i * 30, 20, WHITE);
            }

            // only show Main Menu button for level 3 completion
            menu_ui::DrawMenuButton(menu_btn, "Main Menu", 20);
        } else if (levelComplete) {
            // Level complete but not final level
            int w = MeasureText("Level Complete!", 40);
            menu_ui::DrawTextCenteredRef("Level Complete!", WINDOW_WIDTH/2, 80, 40, GOLD);

            // leaderboard
            menu_ui::DrawTextRef("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                menu_ui::DrawTextCenteredRef(line, WINDOW_WIDTH/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            menu_ui::DrawMenuButton(play_btn, "Next Level", 20);
            menu_ui::DrawMenuButton(menu_btn, "Main Menu", 20);
        } else if (won) {
            int w = MeasureText("You Win!", 40);
            menu_ui::DrawTextCenteredRef("You Win!", WINDOW_WIDTH/2, 80, 40, GOLD);

            // leaderboard
            menu_ui::DrawTextRef("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                menu_ui::DrawTextCenteredRef(line, WINDOW_WIDTH/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            menu_ui::DrawMenuButton(play_btn, "Play Again", 20);
            menu_ui::DrawMenuButton(menu_btn, "Main Menu", 20);
        } else {
            // Game Over
            int w = MeasureText("Game Over", 40);
            menu_ui::DrawTextCenteredRef("Game Over", WINDOW_WIDTH/2, 80, 40, RED);

            // leaderboard
            menu_ui::DrawTextRef("Leaderboard", WINDOW_WIDTH/2 - 80, 160, 25, GOLD);
            int top = std::min((int)entries.size(), 5);
            for (int i = 0; i < top; i++) {
                const char* line = TextFormat("%d. %s - %d",
                    i+1, entries[i].first.c_str(), entries[i].second);
                int lw = MeasureText(line, 20);
                menu_ui::DrawTextCenteredRef(line, WINDOW_WIDTH/2, 200 + i * 30, 20, WHITE);
            }

            // buttons
            menu_ui::DrawMenuButton(play_btn, "Play Again", 20);
            menu_ui::DrawMenuButton(menu_btn, "Main Menu", 20);
        }
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}
