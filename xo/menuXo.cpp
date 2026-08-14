#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "ui/button_helpers.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

//menu
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern Rectangle sfx_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;
int showmenu(){
    BeginDrawing();
    EndDrawing();
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    while(!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle pvp_btn = menu_ui::ReferenceRect(490, 250, 300, 60);
        Rectangle ai_btn = menu_ui::ReferenceRect(490, 350, 300, 60);
        Rectangle back_btn = menu_ui::ReferenceRect(490, 450, 300, 60);
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
            if (CheckCollisionPointRec(mouse_pos, pvp_btn)) {
                return 1;
            }
            if (CheckCollisionPointRec(mouse_pos, ai_btn)) {
                return 2;
            }
            if (CheckCollisionPointRec(mouse_pos, back_btn)) {
                // user clicked Back -> signal "go back to main menu"
                return -1;
            }
        }
        BeginDrawing();
        ClearBackground({20,20,40,225});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef("Arcade Games", 500, 140, 40, WHITE);
        menu_ui::DrawMenuButton(pvp_btn, "Play PvP", 25);
        menu_ui::DrawMenuButton(ai_btn, "Play AI", 25);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
int showAiMenu(){
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    // wait one frame to clear mouse state from previous menu to avoid skipping the menu
    BeginDrawing();
    EndDrawing();
    while(!WindowShouldClose()){
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle easy_btn = menu_ui::ReferenceRect(490, 250, 300, 60);
        Rectangle hard_btn = menu_ui::ReferenceRect(490, 350, 300, 60);
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
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            // zay ely fo8
            if(CheckCollisionPointRec(mouse_pos, easy_btn)) return 1;
            if(CheckCollisionPointRec(mouse_pos, hard_btn)) return 2;
            if(CheckCollisionPointRec(mouse_pos, back_btn)) return 0;
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef("Choose Difficulty", 480, 140, 40, WHITE);
        menu_ui::DrawMenuButton(easy_btn, "Easy", 25);
        menu_ui::DrawMenuButton(hard_btn, "Hard", 25);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
int showPostGameMenu(Player &p1, Player &p2) {
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }

    BeginDrawing();
    EndDrawing();
    while (true) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle same_btn = menu_ui::ReferenceRect(490, 260, 300, 60);
        Rectangle main_btn = menu_ui::ReferenceRect(490, 340, 300, 60);
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else       ResumeMusicStream(bgm);
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }
        if(WindowShouldClose()) break;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
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
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef("Game Over", 560, 140, 40, WHITE);
        // players scores
        menu_ui::DrawTextRef((p1.getName() + ": " + std::to_string(p1.getScore())).c_str(), 490, 180, 25, YELLOW);
        menu_ui::DrawTextRef((p2.getName() + ": " + std::to_string(p2.getScore())).c_str(), 490, 220, 25, YELLOW);

        menu_ui::DrawMenuButton(same_btn, "Play Again", 25);
        menu_ui::DrawMenuButton(main_btn, "Main Menu", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }
    return 0;
}
// user input
bool getPlayerName(Player &p , const std::string& prompt) {
    std::string name="";
    float starX[80], starY[80], starSpeed[80], starSize[80];
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
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
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
        }
#ifdef PLATFORM_WEB
        name = g_webName;
#else
        int key=GetCharPressed();
#endif
        auto m=GetMousePosition();
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) and CheckCollisionPointRec(m, cont_btn) and !name.empty()){
            p.setName(name);
          // signal success to caller
#ifdef PLATFORM_WEB
          EM_ASM({ hideNameKeyboard(); });
#endif
          return true;
        }
        // ESC key also cancels back to main menu
        if(IsKeyPressed(KEY_ESCAPE)) {
#ifdef PLATFORM_WEB
            EM_ASM({ hideNameKeyboard(); });
#endif
            return false;
        }
        // mouse click on Back cancels too
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if(CheckCollisionPointRec(mouse_pos, back_btn)) {
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
        if(key >= 32 && key <= 125) name += (char)key;
#endif


        BeginDrawing();
        ClearBackground({20,20,40,225});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef((prompt+" Enter Your Name:").c_str(), 400, 280, 25, WHITE);
        menu_ui::DrawTextRef(name.c_str(), 410, 320, 25, WHITE);
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
// now returns bool: true = symbol chosen, false = user pressed Back/ESC
bool getPlayerSymbol(Player &p,std::string prompt)
 {
    float starX[80], starY[80], starSpeed[80], starSize[80];
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i] = rand() % 1280; starY[i] = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle x_btn = menu_ui::ReferenceRect(400, 300, 150, 60);
        Rectangle o_btn = menu_ui::ReferenceRect(600, 300, 150, 60);
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
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
        }
        // ESC key cancels back to main menu
        if(IsKeyPressed(KEY_ESCAPE)) return false;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, x_btn)) {
                p.setSymbol('X');
// signal success to caller
return true;
            }
            if (CheckCollisionPointRec(mouse_pos, o_btn)) {
                p.setSymbol('O');
                // signal success to caller
                return true;
            }
            // mouse click on Back cancels too
            if (CheckCollisionPointRec(mouse_pos, back_btn)) return false;
        }
        BeginDrawing();
        ClearBackground({20,20,40,225});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextRef((prompt+" Choose Your Symbol:").c_str(), 380, 220, 25, WHITE);
        menu_ui::DrawMenuButton(x_btn, "X", 30, RED);

        // YELLOW
        menu_ui::DrawMenuButton(o_btn, "O", 30, GREEN);
        menu_ui::DrawMenuButton(back_btn, "Back", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);
        EndDrawing();
    }

    // window closed without choosing -> treat as cancel
    return false;
}
