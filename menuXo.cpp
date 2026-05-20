#include "menuXo.h"

#include <raylib.h>

int showmenu(){
    //buttons
Rectangle pvp_btn={490,250,300,60};
Rectangle ai_btn={490,350,300,60};
Rectangle exit_btn={490,450,300,60};
    while(!WindowShouldClose()) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
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
 DrawText("Arcade Games",500,140,40,WHITE);
        DrawRectangleRec(pvp_btn,DARKBLUE);
        DrawText("Play PvP",600, 265, 25, WHITE);
        DrawRectangleRec(ai_btn,DARKBLUE);
        DrawText("Play AI",600, 365, 25, WHITE);
        DrawRectangleRec(exit_btn,DARKBLUE);
        DrawText("Exit",600, 465, 25, WHITE);
        EndDrawing();
    }
    // DrawText("Choose Difficulty", 480, 140, 40, WHITE);
    // DrawRectangleRec(easy_btn, DARKBLUE);
    // DrawText("Easy", 600, 265, 25, WHITE);
    // DrawRectangleRec(hard_btn, DARKBLUE);
    // DrawText("Hard", 600, 365, 25, WHITE);
    // DrawRectangleRec(back_btn, DARKBLUE);
    // DrawText("exit", 600, 465, 25, WHITE);
}
int showAiMenu(){
    Rectangle easy_btn = {490, 250, 300, 60};
    Rectangle hard_btn = {490, 350, 300, 60};
    Rectangle back_btn = {490, 450, 300, 60};

    // wait one frame to clear mouse state from previous menu to avoid skipping the menu
    BeginDrawing();
    EndDrawing();
    while(!WindowShouldClose()){
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            // zay ely fo8
            if(CheckCollisionPointRec(mouse_pos, easy_btn)) return 1;
            if(CheckCollisionPointRec(mouse_pos, hard_btn)) return 2;
            if(CheckCollisionPointRec(mouse_pos, back_btn)) return 0;
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Choose Difficulty", 480, 140, 40, WHITE);
        DrawRectangleRec(easy_btn, DARKBLUE);
        DrawText("Easy", 600, 265, 25, WHITE);
        DrawRectangleRec(hard_btn, DARKBLUE);
        DrawText("Hard", 600, 365, 25, WHITE);
        DrawRectangleRec(back_btn, DARKBLUE);
        DrawText("exit", 600, 465, 25, WHITE);
        EndDrawing();
    }
    return 0;
}