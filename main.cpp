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
#include <cstdlib>
#include <ctime>
#include <snake_game/main_game/menu_snake.h>
Font font;
bool mutedBGm = false;
Rectangle mute_btn = {20, 660, 80, 40};
Music bgm;
//starts
     int STAR_COUNT = 80;
    float starX[80], starY[80], starSpeed[80], starSize[80];
    // rocket
    float rocketX     = -60.0f;
    float rocketY     = 600.0f;
    float rocketSpeed = 3.0f;

int showmenu_main() {
    BeginDrawing();
    EndDrawing();

    Rectangle xo_btn   = {490, 250, 300, 60};
    Rectangle c4_btn   = {490, 350, 300, 60};
    Rectangle Snake_btn = {490, 450, 300, 60};
    Rectangle exit_btn = {490, 550, 300, 60};

    // stars


    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else          ResumeMusicStream(bgm);

        // update stars
        for (int i = 0; i < STAR_COUNT; i++) {
            starY[i] -= starSpeed[i];
            if (starY[i] < 0) {
                starY[i] = 720;
                starX[i] = rand() % 1280;
            }
        }

        // update rocket
        rocketX += rocketSpeed;
        rocketY -= rocketSpeed * 0.4f;
        if (rocketX > 1400) {
            rocketX = -60;
            rocketY = 600;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, mute_btn)) mutedBGm = !mutedBGm;
            if (CheckCollisionPointRec(mouse_pos, xo_btn))   return 1;
            if (CheckCollisionPointRec(mouse_pos, c4_btn))   return 2;
            if (CheckCollisionPointRec(mouse_pos, Snake_btn)) return 3;
            if (CheckCollisionPointRec(mouse_pos, exit_btn)) return 0;
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});

        // stars
        for (int i = 0; i < STAR_COUNT; i++)
            DrawCircle(starX[i], starY[i], starSize[i], {255, 255, 255, 180});

        // rocket body
        DrawRectanglePro({rocketX, rocketY, 40, 20}, {20, 10}, -25.0f, DARKGRAY);
        // nose
        DrawTriangle(
            {rocketX + 28, rocketY - 8},
            {rocketX + 28, rocketY + 8},
            {rocketX + 48, rocketY},
            RED
        );
        // flame
        DrawTriangle(
            {rocketX - 10, rocketY - 5},
            {rocketX - 10, rocketY + 5},
            {rocketX - 25, rocketY},
            ORANGE
        );
        // window
        DrawCircle(rocketX + 10, rocketY, 5, SKYBLUE);

        // title
        int titleW = MeasureText("Arcade Games", 40);
        DrawText("Arcade Games", 1280/2 - titleW/2, 140, 40, WHITE);

        // buttons
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
        DrawRectangleRec(Snake_btn, DARKBLUE);

        int snW = MeasureText("Snake_game", 25);
        DrawText("Snake_game",
            Snake_btn.x + (Snake_btn.width - snW) / 2,
            Snake_btn.y + (Snake_btn.height - 25) / 2, 25, WHITE);
        DrawRectangleRec(exit_btn, DARKBLUE);
        int exW = MeasureText("Exit", 25);
        DrawText("Exit",
            exit_btn.x + (exit_btn.width - exW) / 2,
            exit_btn.y + (exit_btn.height - 25) / 2, 25, WHITE);

        // mute button
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE",
            mute_btn.x + (mute_btn.width - muteW) / 2,
            mute_btn.y + (mute_btn.height - 20) / 2,
            20, mutedBGm ? GREEN : RED);

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
        if (mutedBGm) PauseMusicStream(bgm);
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
                        if (WindowShouldClose()) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        if (WindowShouldClose()) break;
                        if (!getPlayerName(p2, "Player 2")) break;
                        if (WindowShouldClose()) break;
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
                        if (WindowShouldClose()) break;
                        if (!getPlayerSymbol(p1, p1.getName())) break;
                        if (WindowShouldClose()) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu(); // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        if (WindowShouldClose()) break;
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
                        if (WindowShouldClose()) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        if (WindowShouldClose()) break;
                        if (!getPlayerName_c4(p2, "Player 2")) break;
                        if (WindowShouldClose()) break;
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
                        if (WindowShouldClose()) break;
                        if (!getPlayerSymbol_c4(p1, p1.getName())) break;
                        if (WindowShouldClose()) break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu_c4(); // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        if (WindowShouldClose()) break;
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
                // snake game
                case 3: {
                int mode = showmenu_snake();
                // 0 break , 1 default , 2 lvl
                if (mode == 0) break;
                if (WindowShouldClose()) break;
                        Snake s1;
                        if (!getPlayerName_snake(s1, "")) break;
                        if (WindowShouldClose()) break;
                        if (!getPlayerColor_snake(s1, "")) break;
                        if (WindowShouldClose()) break;
                SnakeGame s_game(s1);
                switch (mode) {
                    case 1: {
                        while (!WindowShouldClose()) {
                            int r = s_game.Default_mode();
                            if (r == 0) break; // main menu
                            // r == 1: play again → loop
                        }
                        break;
                    }
                    case 2: {
                        while (!WindowShouldClose()) {
                            int r1 = s_game.play_gui(1);
                            if (r1 == 0) break;
                            if (r1 == -1) continue; // play again level 1

                            int r2 = s_game.play_gui(2);
                            if (r2 == 0) break;
                            if (r2 == -1) continue; // play again from level 1

                            int r3 = s_game.play_gui(3);
                            if (r3 == 0) break;
                            break; // all levels done → back to main menu
                        }
                        break;
                    }
                }
                BeginDrawing(); EndDrawing();
                break;
            }

                // case 3: new game here
        }
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

/*
int main() {
    srand(time(nullptr));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int choice = showmenu_snake();
        if (choice == 0) break;

        Snake s1;
        SnakeGame game(s1);

        if (!getPlayerName_snake(s1, "")) continue;
        if (!getPlayerColor_snake(s1, "")) continue;

        if (choice == 1) {
            // free for all mode
            while (!WindowShouldClose()) {
                int r = game.Default_mode();
                if (r == 0) break; // main menu
                // r == 1: play again
            }
        } else if (choice == 2) {
            // levels mode
            while (!WindowShouldClose()) {
                int r1 = game.play_gui(1);
                if (r1 == 0) break;           // main menu
                if (r1 == -1) continue;        // play again level 1

                int r2 = game.play_gui(2);
                if (r2 == 0) break;
                if (r2 == -1) {
                    game.play_gui(1);
                    continue;
                }

                int r3 = game.play_gui(3);
                if (r3 == 0) break;
                // finished all levels → back to menu
                break;
            }
        }
    }

    CloseWindow();
    return 0;
}
*/