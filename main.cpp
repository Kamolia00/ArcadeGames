#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
#include "raylib.h"
Font font;
int showmenu_main() {
    BeginDrawing();
    EndDrawing();

    Rectangle xo_btn   = {490, 250, 300, 60};
    Rectangle c4_btn   = {490, 350, 300, 60};
    Rectangle exit_btn = {490, 450, 300, 60};

    while (!WindowShouldClose()) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, xo_btn))   return 1;
            if (CheckCollisionPointRec(mouse_pos, c4_btn))   return 2;
            if (CheckCollisionPointRec(mouse_pos, exit_btn)) return 0;
        }
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Arcade Games", 500, 140, 40, WHITE);
        DrawRectangleRec(xo_btn,   DARKBLUE);
        DrawText("Tic-Tac-Toe", 545, 265, 25, WHITE);
        DrawRectangleRec(c4_btn,   DARKBLUE);
        DrawText("Connect 4",   560, 365, 25, WHITE);
        DrawRectangleRec(exit_btn, DARKBLUE);
        DrawText("Exit",        620, 465, 25, WHITE);
        EndDrawing();
    }
    return 0;
}
int main() {
    InitWindow(1280, 720, "Arcade Games");
    SetTargetFPS(60);
    font = LoadFont("C:/Windows/Fonts/arial.ttf");

    while (!WindowShouldClose()) {
        int game = showmenu_main();   // 1=XO, 2=C4, 0=exit
        if (game == 0) break;

        Player p1, p2, ai;
        ai.setName("AI");
//1 xo 2 c4 3 exit
        switch (game) {

            case 1: {  // XO
                int mode = showmenu();  // 1=PvP, 2=AI, 0=back
                if (mode == 0) break;

                switch (mode) {
                    case 1: {  // PvP
                        while (!WindowShouldClose()) {
                            if (!getPlayerName(p1, "Player 1"))           break;
                            if (!getPlayerSymbol(p1, p1.getName()))         break;
                            if (!getPlayerName(p2, "Player 2"))           break;
                            p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                            XO game(p1, p2);
                            game.playGameGUI_pvp();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {  // vs AI
                        if (!getPlayerName(p1, "Player 1"))         break;
                        if (!getPlayerSymbol(p1, p1.getName()))     break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu();  // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            XO game(p1, ai);
                            switch (diff) {
                                case 1: game.playGameGUI_ai_easy(); break;
                                case 2: game.playGameGUI_ai_hard(); break;
                            }
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu(p1, ai) == 0) break;
                        }
                        break;
                    }
                }
                break;
            }

            case 2: {  // Connect 4
                int mode = showmenu_c4();  // 1=PvP, 2=AI, 0=back
                if (mode == 0) break;
                switch (mode) {
                    case 1: {  // PvP
                        while (!WindowShouldClose()) {
                            if (!getPlayerName_c4(p1, "Player 1"))          break;
                            if (!getPlayerSymbol_c4(p1, p1.getName()))      break;
                            if (!getPlayerName_c4(p2, "Player 2"))          break;
                            p2.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                            connect4 game(p1, p2);
                            game.pvp_gui();
                            if (WindowShouldClose()) break;
                            if (showPostGameMenu_c4(p1, p2) == 0) break;
                        }
                        break;
                    }
                    case 2: {  // vs AI
                        if (!getPlayerName_c4(p1, "Player 1"))          break;
                        if (!getPlayerSymbol_c4(p1, p1.getName()))      break;
                        ai.setSymbol(p1.getSymbol() == 'X' ? 'O' : 'X');
                        int diff = showAiMenu_c4();  // 1=easy, 2=hard, 0=back
                        if (diff == 0) break;
                        while (!WindowShouldClose()) {
                            connect4 game(p1, ai);
                            switch (diff) {
                                case 1: game.ai_ez_gui();   break;
                                case 2: game.ai_hard_gui(); break;
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

    CloseWindow();
    return 0;
}