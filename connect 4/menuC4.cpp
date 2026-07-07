#include "xo/xo.h"

#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "ui/button_helpers.h"
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
    Rectangle back_btn={490,450,300,60};

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
            if (CheckCollisionPointRec(mouse_pos, back_btn)) {
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
        menu_ui::DrawMenuButton(pvp_btn, "Play PvP", 25);
        menu_ui::DrawMenuButton(ai_btn, "Play AI", 25);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
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
        menu_ui::DrawMenuButton(easy_btn, "Easy", 25);
        menu_ui::DrawMenuButton(hard_btn, "Hard", 25);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
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

        menu_ui::DrawMenuButton(same_btn, "Play Again", 25);
        menu_ui::DrawMenuButton(main_btn, "Main Menu (Enter)", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
bool getPlayerName_c4(Player &p , const std::string& prompt) {
    string name="";
    Rectangle back_btn={490,510,300,60};
    Rectangle cont_btn={490,400,300,60};
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
        auto m=GetMousePosition();
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) and CheckCollisionPointRec(m, cont_btn) and !name.empty()){
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
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(cont_btn, "Continue", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
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
        menu_ui::DrawMenuButton(red_btn, "RED", 30, RED);

        // YELLOW
        menu_ui::DrawMenuButton(yellow_btn, "YELLOW", 30, {255, 200, 0, 255});
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}