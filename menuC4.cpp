#include"menuC4.h"
#include <string>
using namespace std;
//menu
int showmenu_c4(){
    BeginDrawing();
    EndDrawing();
    //buttons
    Rectangle pvp_btn={490,250,300,60};
    Rectangle ai_btn={490,350,300,60};
    Rectangle exit_btn={490,450,300,60};
    while(!WindowShouldClose()) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            // 1 pvp
            //2 ai
            //0 exit
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
        DrawText("Connect 4",520,140,40,WHITE);
        // red and yellow accents for Connect 4 disks
        DrawRectangleRec(pvp_btn,DARKBLUE);
        DrawText("Play PvP",600, 265, 25, WHITE);
        DrawRectangleRec(ai_btn,DARKBLUE);
        DrawText("Play AI",600, 365, 25, WHITE);
        DrawRectangleRec(exit_btn,DARKBLUE);
        DrawText("Exit",600, 465, 25, WHITE);
        EndDrawing();
    }
    return 0;
}
int showPostGameMenu_c4(Player &p1, Player &p2) {
    Rectangle same_btn = {490, 260, 300, 60};
    Rectangle main_btn = {490, 340, 300, 60};
    BeginDrawing();
    EndDrawing();
    while (true) {
        if (WindowShouldClose()) break;
        // Enter key -> main menu
        if (IsKeyPressed(KEY_ENTER)) {
            return 0;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            // 1 = play again with same players, 0 = main menu
            if (CheckCollisionPointRec(mouse_pos, same_btn)) {
                return 1;
            }
            if (CheckCollisionPointRec(mouse_pos, main_btn)) {
                return 0;
            }
        }
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Game Over", 560, 140, 40, WHITE);
        // players scores
        DrawText((p1.getName() + ": " + std::to_string(p1.getScore())).c_str(), 490, 180, 25, YELLOW);
        DrawText((p2.getName() + ": " + std::to_string(p2.getScore())).c_str(), 490, 220, 25, YELLOW);

        DrawRectangleRec(same_btn, DARKBLUE);
        DrawText("Play Again", 560, 275, 25, WHITE);
        DrawRectangleRec(main_btn, DARKBLUE);
        DrawText("Main Menu (Enter)", 525, 355, 25, WHITE);

        EndDrawing();
    }
    return 0;
}
