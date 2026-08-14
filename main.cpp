#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "raylib.h"
#include "snake_game/snake/snake.h"
#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"
#include "pong/pong game/pong.h"
#include "pong/pong game/ball.h"
#include "pong/menus/menu_pong.h"
#include <snake_game/main_game/menu_snake.h>
#include "ui/button_helpers.h"
#include <cstdlib>
#include <ctime>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

Font font;
bool mutedBGm = false;
Rectangle mute_btn = menu_ui::ReferenceRect(20, 660, 100, 40);
Rectangle sfx_btn  = menu_ui::ReferenceRect(140, 660, 120, 40);
Music bgm;
int STAR_COUNT = 80;
float starX[80], starY[80], starSpeed[80], starSize[80];
float rocketX = -60.0f;
float rocketY = 600.0f;
float rocketSpeed = 3.0f;

#ifdef PLATFORM_WEB
static EM_BOOL SyncWindowSizeToCanvas(int, const EmscriptenUiEvent*, void*) {
    double cssWidth = 0.0;
    double cssHeight = 0.0;
    emscripten_get_element_css_size("#canvas", &cssWidth, &cssHeight);
    const double devicePixelRatio = emscripten_get_device_pixel_ratio();
    SetWindowSize(static_cast<int>(cssWidth * devicePixelRatio),
                  static_cast<int>(cssHeight * devicePixelRatio));
    return EM_TRUE;
}
#endif

int showmenu_main() {
    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        menu_ui::SyncAudioButtonRects(mute_btn, sfx_btn);
        Rectangle xo_btn    = menu_ui::ReferenceRect(490, 250, 300, 60);
        Rectangle c4_btn    = menu_ui::ReferenceRect(490, 320, 300, 60);
        Rectangle snake_btn = menu_ui::ReferenceRect(490, 390, 300, 60);
        Rectangle pong_btn  = menu_ui::ReferenceRect(490, 460, 300, 60);
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else          ResumeMusicStream(bgm);

        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) { starY[i] = 720; starX[i] = rand() % 1280; }
        }
        rocketX += rocketSpeed; rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) { rocketX = -60; rocketY = 600; }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(m, xo_btn))    return 1;
            if (CheckCollisionPointRec(m, c4_btn))    return 2;
            if (CheckCollisionPointRec(m, snake_btn)) return 3;
            if (CheckCollisionPointRec(m, pong_btn))  return 4;
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        menu_ui::DrawMenuBackdrop(starX, starY, starSize, STAR_COUNT, rocketX, rocketY);
        menu_ui::DrawTextCenteredRef("Arcade Games", 640, 130, 40, WHITE);

        menu_ui::DrawMenuButton(xo_btn, "Tic-Tac-Toe", 25);
        menu_ui::DrawMenuButton(c4_btn, "Connect 4", 25);
        menu_ui::DrawMenuButton(snake_btn, "Snake", 25);
        menu_ui::DrawMenuButton(pong_btn, "Pong", 25);
        menu_ui::DrawMenuButton(mute_btn, mutedBGm ? "SOUND" : "MUTE", 20, mutedBGm ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}

int main() {
    for (int i = 0; i < STAR_COUNT; i++) {
        starX[i]     = rand() % 1280;
        starY[i]     = rand() % 720;
        starSpeed[i] = 0.5f + (rand() % 20) / 10.0f;
        starSize[i]  = 1.0f + (rand() % 3);
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280,720,"Arcade");
#ifdef PLATFORM_WEB
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false, SyncWindowSizeToCanvas);
    SyncWindowSizeToCanvas(0, nullptr, nullptr);
#endif
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(60);
    bgm = LoadMusicStream("assets/sounds/main_menu.mp3");
    SetMusicVolume(bgm, 0.5f);
    PlayMusicStream(bgm);
    font = LoadFont("C:/Windows/Fonts/arial.ttf");

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        int game = showmenu_main();
        if (game == 0) break;

        Player p1, p2, ai;
        ai.setName("AI");
//1 xo ,c4,snake,pong
        switch (game) {
            case 1: {
                int mode = showmenu();
                if (mode == 0) break;
                switch (mode) {
                    case 1: {
                        if (!getPlayerName(p1, "Player 1")) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        if (!getPlayerName(p2, "Player 2")) break;
                        p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        while (!WindowShouldClose()) {
                            XO xgame(p1, p2);
                            xgame.playGameGUI_pvp();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {
                        if (!getPlayerName(p1, "Player 1")) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu();
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            XO xgame(p1, ai);
                            switch (diff) {
                                case 1: xgame.playGameGUI_ai_easy(); break;
                                case 2: xgame.playGameGUI_ai_hard(); break;
                            }
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu(p1, ai) == 0) break;
                        }
                        break;
                    }
                }
                break;
            }

            case 2: {
                int mode = showmenu_c4();
                if (mode == 0) break;
                switch (mode) {
                    case 1: {
                        if (!getPlayerName_c4(p1, "Player 1")) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        if (!getPlayerName_c4(p2, "Player 2")) break;
                        p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        while (!WindowShouldClose()) {
                            connect4 cgame(p1, p2);
                            cgame.pvp_gui();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu_c4(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {
                        if (!getPlayerName_c4(p1, "Player 1")) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu_c4();
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            connect4 cgame(p1, ai);
                            switch (diff) {
                                case 1: cgame.ai_ez_gui(); break;
                                case 2: cgame.ai_hard_gui(); break;
                            }
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu_c4(p1, ai) == 0) break;
                        }
                        break;
                    }
                }
                break;
            }

            case 3: {
                int mode = showmenu_snake();
                if (mode == 0) break;
                Snake s1;
                if (!getPlayerName_snake(s1, "")) break;
                if (!getPlayerColor_snake(s1, "")) break;
                SnakeGame s_game(s1);
                switch (mode) {
                    case 1: {
                        while (!WindowShouldClose()) {
                            int r = s_game.Default_mode();
                            if (r == 0) break;
                        }
                        break;
                    }
                    case 2: {
                        while (!WindowShouldClose()) {
                            int r1 = s_game.play_gui(1);
                            if (r1 == 0) break;
                            if (r1 == -1) continue;
                            int r2 = s_game.play_gui(2);
                            if (r2 == 0) break;
                            if (r2 == -1) continue;
                            int r3 = s_game.play_gui(3);
                            if (r3 == 0) break;
                            break;
                        }
                        break;
                    }
                }
                BeginDrawing(); EndDrawing();
                break;
            }

            case 4: {
                int mode = showmenu_pong();
                if (mode == 0) break;
                Ball b(0, 0, 0, 0, 0);
                switch (mode) {
                    case 1: {
                        if (!getPlayerName_pong(p1, "Player 1 - Controls: W / S")) break;
                        if (!getPlayerColor_pong(p1)) break;
                        if (!getPlayerName_pong(p2, "Player 2 - Controls: UP / DOWN")) break;
                        if (!getPlayerColor_pong(p2)) break;
                        int t = setThreshold_pong();
                        if (t == -1) break;
                        Pong pgame(p1, p2, b, t);
                        while (!WindowShouldClose()) {
                            pgame.playGame_pvp();
                            int r = showPostGame_menu_pong(p1, p2, pgame.getGamesP1(), pgame.getGamesP2());
                            if (r == 1) break;
                        }
                        break;
                    }
                    case 2: {
                        if (!getPlayerName_pong(p1, "Player - Controls: W / S")) break;
                        if (!getPlayerColor_pong(p1)) break;
                        int t = setThreshold_pong();
                        if (t == -1) break;
                        p2.setName("AI");
                        Pong pgame(p1, p2, b, t);
                        while (!WindowShouldClose()) {
                            pgame.playGame_ai();
                            int r = showPostGame_menu_pong(p1,p2,pgame.getGamesP1(),pgame.getGamesP2());
                            if (r == 1) break;
                        }
                        break;
                    }
                }
                BeginDrawing(); EndDrawing();
                break;
            }
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
