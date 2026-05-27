#include "connect4.h"
#include "menuC4.h"
#include "player.h"

Font font;

int main() {
    InitWindow(1280, 720, "Arcade Games");
    SetTargetFPS(60);
    // custom font
    font = LoadFont("C:/Windows/Fonts/arial.ttf");

    Player p1("kamal", 'O'), p2("hima", 'O'), ai("ai", 'X');

    while (!WindowShouldClose()) {
        int choice = showmenu_c4();
        // 0 = exit, 1 = PvP, 2 = AI
        if (choice == 0) break;

        if (choice == 1) {
            // PvP: keep replaying while user picks "Play Again"
            while (!WindowShouldClose()) {
                connect4 game(p1, p2);
                game.pvp_gui();
                if (WindowShouldClose()) break;
                const int after = showPostGameMenu_c4(p1, p2);
                // 0 = main menu, 1 = play again with same players
                if (after == 0) break;
            }
        }
        else if (choice == 2) {
            while (!WindowShouldClose()) {
                connect4 game(p1, ai);
                game.ai_hard_gui();
                if (WindowShouldClose()) break;
                const int after = showPostGameMenu_c4(p1, ai);
                if (after == 0) break;
            }
        }
    }

    CloseWindow();
    return 0;
}
