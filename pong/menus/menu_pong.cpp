#include"pong/menus/menu_pong.h"
#include "ui/button_helpers.h"
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;

int showmenu_pong() {
    BeginDrawing(); EndDrawing();
    Rectangle pvp={490,250,300,60};
    Rectangle ai={490,350,300,60};
    Rectangle back={490,450,300,60};
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
            if (CheckCollisionPointRec(mousePos, mute_btn))
                mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mousePos,pvp))
                return 1;
            if (CheckCollisionPointRec(mousePos,ai))
                return 2;
            if (CheckCollisionPointRec(mousePos,back))
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
        DrawText("Pong Game",520,140,40,WHITE);
         menu_ui::DrawMenuButton(pvp, "Player vs Player", 25);
         menu_ui::DrawMenuButton(ai, "Player vs AI", 25);
         menu_ui::DrawMenuButton(back, "Back", 25);
         menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}
bool getPlayerName_pong(Player &p, const std::string prompt) {
    std::string name = "";
    Rectangle back_btn = {490, 450, 300, 60};
    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
            for (int i = 0; i < STAR_COUNT; i++) {
                starY[i] -= starSpeed[i];
                if (starY[i] < 0) {
                    starY[i] = 720; starX[i] = rand() % 1280;
                }
            }
            rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
            if (rocketX > 1400) {
                rocketX = -60; rocketY = 600;
            }
        if (IsKeyPressed(KEY_ENTER) && !name.empty()) {
            p.setName(name);
            return true;
        }
        if (IsKeyPressed(KEY_ESCAPE)) return false;
        int key = GetCharPressed();
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn))
                mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(m, back_btn)) {
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) name.pop_back();
        if (key >= 32 && key <= 125) name += (char)key;

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText(prompt.c_str(), 400, 220, 25, SKYBLUE);
        DrawText("Enter Your Name:", 400, 280, 25, WHITE);
        DrawText(name.c_str(), 400, 320, 25, YELLOW);
        DrawText("Press Enter to Continue", 400, 370, 20, GRAY);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return false;
}
int showPostGame_menu_pong(Player p1,Player p2, int g1,int g2) {
    Rectangle again_btn = {490, 340, 300, 60};
    Rectangle back_btn = {490, 410, 300, 60};
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
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, mute_btn)) mutedBGm = !mutedBGm;
        if (CheckCollisionPointRec(mousePos, again_btn))
            return 2;
        if (CheckCollisionPointRec(mousePos, back_btn))
            return 1;
    }
BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    for (int i = 0; i < STAR_COUNT; i++)
        DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
    DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
    DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
    DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
    DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
    DrawText("Game Over", 560, 140, 40, WHITE);
        DrawText((p1.getName() + ": " + std::to_string(g1)).c_str(), 490, 220, 25, YELLOW);
        DrawText((p2.getName() + ": " + std::to_string(g2)).c_str(), 490, 260, 25, YELLOW);
   menu_ui::DrawMenuButton(again_btn, "Play Again", 25);
   menu_ui::DrawMenuButton(back_btn, "Main Menu", 25);
   menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

    EndDrawing();
}
    return 0;
}
bool getPlayerColor_pong(Player &p) {
    Rectangle green_btn = {260, 300, 150, 60};
    Rectangle red_btn   = {440, 300, 150, 60};
    Rectangle blue_btn  = {620, 300, 150, 60};
    Rectangle white  = {800, 300, 150, 60};
    Rectangle back_btn  = {490, 450, 300, 60};
    int selected = -1; // no color initially selected

    // wait one frame to clear previous input state
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) {
            p.setSymbol('g');
            return true;
        }
        if (IsKeyPressed(KEY_TWO)) {
            p.setSymbol('r');
            return true;
        }
        if (IsKeyPressed(KEY_THREE)) {
            p.setSymbol('b');
            return true;
        }
        if (IsKeyPressed(KEY_FOUR)) {
            p.setSymbol('w');
            return true;
        }
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
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, green_btn)) {
                p.setSymbol('g');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, red_btn)) {
                p.setSymbol('r');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, blue_btn)) {
                p.setSymbol('b');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, white)) {
                p.setSymbol('w');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, back_btn)) {
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        Vector2 mouse_pos = GetMousePosition();
        selected = -1;
        if (CheckCollisionPointRec(mouse_pos, green_btn)) selected = 0;
        else if (CheckCollisionPointRec(mouse_pos, red_btn)) selected = 1;
        else if (CheckCollisionPointRec(mouse_pos, blue_btn)) selected = 2;
        else if (CheckCollisionPointRec(mouse_pos, white)) selected = 3;
        BeginDrawing();
        ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText((p.getName() + " Choose Your Color:").c_str(), 420, 220, 25, WHITE);
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

        DrawRectangleRec(white, selected == 3 ? Color{50, 150, 200, 255} : DARKBLUE);
        int dW = MeasureText("WHITE", 24);
        DrawText("WHITE",
                 white.x + (white.width - dW) / 2,
                 white.y + (white.height - 24) / 2, 24, WHITE);

        // Back button
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}

int setThreshold_pong() {
    std::string input = "";
    std::string error = "";
    Rectangle back_btn = {490, 450, 300, 60};
    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }

        int key = GetCharPressed();

        if (IsKeyPressed(KEY_ENTER)) {
            if (input.empty()) {
                error = "Please enter a number!";
            } else {
                int val = std::stoi(input);
                if (val < 1 || val > 8) {
                    error = "Enter a number between 1 and 8!";
                    input = "";
                } else {
                    return val;
                }
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) {
            input.pop_back();
            error = "";
        }
        if (key >= '1' && key <= '9' && input.size() < 1) {
            input += (char)key;
            error = "";
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(m, back_btn)) {
                BeginDrawing(); EndDrawing();
                return -1;
            }
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText("Set Score Limit", 490, 140, 35, WHITE);
        DrawText("Enter max score (1-8):", 490, 220, 25, WHITE);
        DrawText(input.c_str(), 490, 270, 40, YELLOW);
        if (!error.empty())
            DrawText(error.c_str(), 490, 330, 20, RED);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return -1;
}