#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "raylib.h"
Font font;
bool muted = false;
Rectangle mute_btn = {20, 660, 80, 40};
Music bgm;

int showmenu_main() {
    BeginDrawing();
    EndDrawing();

    Rectangle xo_btn = {490, 250, 300, 60};
    Rectangle c4_btn = {490, 350, 300, 60};
    Rectangle exit_btn = {490, 450, 300, 60};
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (muted)
            PauseMusicStream(bgm);
        else
            ResumeMusicStream(bgm);

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn))
                muted = !muted;
            if (CheckCollisionPointRec(mouse_pos, xo_btn))
                return 1;
            if (CheckCollisionPointRec(mouse_pos, c4_btn)) return 2;
            if (CheckCollisionPointRec(mouse_pos, exit_btn)) return 0;
        }
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Arcade Games", 500, 140, 40, WHITE);
        DrawRectangleRec(xo_btn, DARKBLUE);
        int ttW = MeasureText("Tic-Tac-Toe", 25);
        DrawText("Tic-Tac-Toe",
                 xo_btn.x + (xo_btn.width - ttW) / 2,
                 xo_btn.y + (xo_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(c4_btn, DARKBLUE);
        int c4W = MeasureText("Connect 4", 25);
        DrawText("Connect 4",
                 c4_btn.x + (c4_btn.width - c4W) / 2,
                 c4_btn.y + (c4_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(exit_btn, DARKBLUE);
        int exW = MeasureText("Exit", 25);
        DrawText("Exit",
                 exit_btn.x + (exit_btn.width - exW) / 2,
                 exit_btn.y + (exit_btn.height - 25) / 2, 25, WHITE);
        // mute button
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(muted ? "SOUND" : "MUTE", 20);
        DrawText(muted ? "SOUND" : "MUTE", mute_btn.x + (mute_btn.width - muteW) / 2,
                 mute_btn.y + (mute_btn.height - 20) / 2, 20, muted ? GREEN : RED);

        EndDrawing();
    }
    return 0;
}

int main() {
    InitWindow(1280, 720, "Arcade Games");
    InitAudioDevice();
    SetTargetFPS(60);
    bgm = LoadMusicStream("D:/ArcadeGames/assets/sounds/main_menu.mp3");
    SetMusicVolume(bgm, 0.5f);
    PlayMusicStream(bgm);
    font = LoadFont("C:/Windows/Fonts/arial.ttf");

    while (!WindowShouldClose()) {
        // 1=XO, 2=C4, 0=exit
        UpdateMusicStream(bgm);
        if (muted) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        int game = showmenu_main();
        if (game == 0) break;

        Player p1, p2, ai;
        ai.setName("AI");
        //1 xo 2 c4 3 exit
        switch (game) {
            case 1: {
                // XO
                int mode = showmenu(); // 1=PvP, 2=AI, 0=back
                if (mode == 0) break;

                switch (mode) {
                    case 1: {
                        // PvP
                        if (!getPlayerName(p1, "Player 1")) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        if (!getPlayerName(p2, "Player 2")) break;
                        p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        while (!WindowShouldClose()) {
                            XO game(p1, p2);
                            game.playGameGUI_pvp();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {
                        // vs AI
                        if (!getPlayerName(p1, "Player 1")) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu(); // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            XO game(p1, ai);
                            switch (diff) {
                                case 1: game.playGameGUI_ai_easy();
                                    break;
                                case 2: game.playGameGUI_ai_hard();
                                    break;
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
                // Connect 4
                int mode = showmenu_c4(); // 1=PvP, 2=AI, 0=back
                if (mode == 0) break;
                switch (mode) {
                    case 1: {
                        // PvP
                        if (!getPlayerName_c4(p1, "Player 1")) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        if (!getPlayerName_c4(p2, "Player 2")) break;
                        p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        while (!WindowShouldClose()) {
                            connect4 game(p1, p2);
                            game.pvp_gui();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu_c4(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {
                        // vs AI
                        if (!getPlayerName_c4(p1, "Player 1")) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu_c4(); // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            connect4 game(p1, ai);
                            switch (diff) {
                                case 1: game.ai_ez_gui();
                                    break;
                                case 2: game.ai_hard_gui();
                                    break;
                            }
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu_c4(p1, ai) == 0) break;
                        }
                        break;
                    }
                }
                break;
            }

                // case 3: new game here
        }
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
