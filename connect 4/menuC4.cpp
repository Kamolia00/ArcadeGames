#include "xo/xo.h"

#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include <string>
using namespace std;
//menu
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;
int showmenu_c4(){
    BeginDrawing();
    EndDrawing();
    //buttons
    Rectangle pvp_btn={490,250,300,60};
    Rectangle ai_btn={490,350,300,60};
    Rectangle exit_btn={490,450,300,60};

    while(!WindowShouldClose()) {
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
            Vector2 mouse_pos = GetMousePosition();
            // 1 pvp
            //2 ai
            //0 back
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, pvp_btn)) {
                return 1;
            }
            if (CheckCollisionPointRec(mouse_pos, ai_btn)) {
                return 2;
            }
            if (CheckCollisionPointRec(mouse_pos, exit_btn)) {
                // no button is pressed or left
                return 0;
            }
        }
        BeginDrawing();
        ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText("Connect 4",520,140,40,WHITE);
        // red and yellow accents for Connect 4 disks
        DrawRectangleRec(pvp_btn,DARKBLUE);
        int pvpW = MeasureText("Play PvP", 25);
        DrawText("Play PvP",
                 pvp_btn.x + (pvp_btn.width - pvpW) / 2,
                 pvp_btn.y + (pvp_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(ai_btn,DARKBLUE);
        int aiW = MeasureText("Play AI", 25);
        DrawText("Play AI",
                 ai_btn.x + (ai_btn.width - aiW) / 2,
                 ai_btn.y + (ai_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(exit_btn,DARKBLUE);
        int exW = MeasureText("Back", 25);
        DrawText("Back",
                 exit_btn.x + (exit_btn.width - exW) / 2,
                 exit_btn.y + (exit_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
int showAiMenu_c4(){
    Rectangle easy_btn = {490, 250, 300, 60};
    Rectangle hard_btn = {490, 350, 300, 60};
    Rectangle back_btn = {490, 450, 300, 60};
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    // wait one frame to clear mouse state from previous menu to avoid skipping the menu
    BeginDrawing();
    EndDrawing();
    while(!WindowShouldClose()){
        UpdateMusicStream(bgm);
        if (mutedBGm)
            PauseMusicStream(bgm);
        else
            ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            // zay ely fo8
            if(CheckCollisionPointRec(mouse_pos, easy_btn)) return 1;
            if(CheckCollisionPointRec(mouse_pos, hard_btn)) return 2;
            if(CheckCollisionPointRec(mouse_pos, back_btn)) return 0;
        }
//hard=1 easy=2 back=0
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText("Choose Difficulty", 480, 140, 40, WHITE);
        DrawRectangleRec(easy_btn, DARKBLUE);
        int easyW = MeasureText("Easy", 25);
        DrawText("Easy",
                 easy_btn.x + (easy_btn.width - easyW) / 2,
                 easy_btn.y + (easy_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(hard_btn, DARKBLUE);
        int hardW = MeasureText("Hard", 25);
        DrawText("Hard",
                 hard_btn.x + (hard_btn.width - hardW) / 2,
                 hard_btn.y + (hard_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("exit", 25);
        DrawText("exit",
                 back_btn.x + (back_btn.width - backW) / 2,
                 back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
int showPostGameMenu_c4(Player &p1, Player &p2) {
    Rectangle same_btn = {490, 260, 300, 60};
    Rectangle main_btn = {490, 340, 300, 60};
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
     BeginDrawing();
     EndDrawing();
     while (!WindowShouldClose()) {
         UpdateMusicStream(bgm);
         if (mutedBGm)
             PauseMusicStream(bgm);
         else
             ResumeMusicStream(bgm);
         for (int i = 0; i < STAR_COUNT; i++) {
             starY[i] -= starSpeed[i];
             if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
         }
         rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
         if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        // Enter key -> main menu
        if (IsKeyPressed(KEY_ENTER)) {
            return 0;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            // 1 = play again with same players, 0 = main menu
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, same_btn)) {
                return 1;
            }
            if (CheckCollisionPointRec(mouse_pos, main_btn)) {
                return 0;
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
        DrawText("Game Over", 560, 140, 40, WHITE);
        // players scores
        DrawText((p1.getName() + ": " + std::to_string(p1.getScore())).c_str(), 490, 180, 25, YELLOW);
        DrawText((p2.getName() + ": " + std::to_string(p2.getScore())).c_str(), 490, 220, 25, YELLOW);

        DrawRectangleRec(same_btn, DARKBLUE);
        int sameW = MeasureText("Play Again", 25);
        DrawText("Play Again",
                 same_btn.x + (same_btn.width - sameW) / 2,
                 same_btn.y + (same_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(main_btn, DARKBLUE);
        int mainW = MeasureText("Main Menu (Enter)", 25);
        DrawText("Main Menu (Enter)",
                 main_btn.x + (main_btn.width - mainW) / 2,
                 main_btn.y + (main_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2, mute_btn.y + (mute_btn.height - 20) / 2, 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
bool getPlayerName_c4(Player &p , const std::string& prompt) {
    string name="";
    Rectangle back_btn={490,450,300,60};
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm)
            PauseMusicStream(bgm);
        else
            ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
        }
        int key=GetCharPressed();
        if(IsKeyPressed(KEY_ENTER) and !name.empty()){
            p.setName(name);
            // signal success to caller
            return true;
        }
    // ESC key also cancels back to main menu
    if(IsKeyPressed(KEY_ESCAPE)) return false;
    // mouse click on Back cancels too
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
        Vector2 mouse_pos = GetMousePosition();
        if(CheckCollisionPointRec(mouse_pos, back_btn)) return false;
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
// now returns bool: true = symbol chosen, false = user pressed Back/ESC
bool getPlayerSymbol_c4(Player &p,std::string prompt){
    Rectangle red_btn={400,300,150,60};
    Rectangle yellow_btn={600,300,150,60};
    // back button rectangle (added so the user can return to the main menu)
    Rectangle back_btn={490,450,300,60};
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if
        (mutedBGm) PauseMusicStream(bgm);
        else
            ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        // ESC key cancels back to main menu
        if(IsKeyPressed(KEY_ESCAPE)) return false;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, red_btn)) {
                p.setSymbol('X');
                // signal success to caller
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, yellow_btn)) {
                p.setSymbol('O');
                // signal success to caller
                return true;
            }
            // mouse click on Back cancels too
            if (CheckCollisionPointRec(mouse_pos, back_btn)) return false;
        }
        BeginDrawing();
        ClearBackground({20,20,40,225});
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        DrawTriangle({rocketX+28,rocketY-8},{rocketX+28,rocketY+8},{rocketX+48,rocketY}, RED);
        DrawTriangle({rocketX-10,rocketY-5},{rocketX-10,rocketY+5},{rocketX-25,rocketY}, ORANGE);
        DrawCircle(rocketX+10, rocketY, 5, SKYBLUE);
        DrawText((prompt+" Choose Your Symbol:").c_str(), 380, 220, 25, WHITE);
        DrawRectangleRec(red_btn, DARKBLUE);
        // RED
        int redW = MeasureText("RED", 30);
        DrawText("RED",
            red_btn.x + (red_btn.width - redW) / 2,red_btn.y + (red_btn.height - 30) / 2,30, RED);

        // YELLOW
        DrawRectangleRec(yellow_btn, DARKBLUE);
        int yellowW = MeasureText("YELLOW", 30);
        DrawText("YELLOW",
            yellow_btn.x + (yellow_btn.width - yellowW) / 2,
            yellow_btn.y + (yellow_btn.height - 30) / 2,
            30, {255, 200, 0, 255});
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