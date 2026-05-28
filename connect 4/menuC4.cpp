#include "xo/xo.h"
#include "xo/menuXo.h"
#include "connect 4/connect4.h"
#include "connect 4/menuC4.h"
#include "player stuff/player.h"
#include "player stuff/valid_input.h"
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
int showAiMenu_c4(){Rectangle easy_btn = {490, 250, 300, 60};
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
//hard=1 easy=2 back=0
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
bool getPlayerName_c4(Player &p , const std::string& prompt) {
    string name="";
    Rectangle back_btn={490,450,300,60};

    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
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
    DrawText((prompt+" Enter Your Name:").c_str(), 400, 280, 25, WHITE);
    DrawText(name.c_str(), 400, 320, 25, WHITE);
    DrawText("Press Enter to Continue", 400, 380, 20, WHITE);
    // draw the Back button
    DrawRectangleRec(back_btn, DARKBLUE);
    DrawText("Back", 600, 465, 25, WHITE);
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
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        // ESC key cancels back to main menu
        if(IsKeyPressed(KEY_ESCAPE)) return false;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
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

        DrawText("Back", 600, 465, 25, WHITE);
        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}