#include "menuXo.h"

#include <raylib.h>
//menu
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
    return 0;
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
int showPostGameMenu(bool is_ai) {
    Rectangle same_btn = {490, 200, 300, 60};
    Rectangle new_btn = {490, 300, 300, 60};
    Rectangle switch_btn = {490, 400, 300, 60};
    Rectangle main_btn = {490, 500, 300, 60};
    BeginDrawing();
    EndDrawing();
    while (true) {
        if(WindowShouldClose()) break;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, same_btn)) {
                return 1;
            }
            if (CheckCollisionPointRec(mouse_pos, new_btn)) {
                return 2;
            }
            if (CheckCollisionPointRec(mouse_pos, switch_btn)) {
                return 3;
            }
            if (CheckCollisionPointRec(mouse_pos, main_btn)) {
                return 0;
            }
        }
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Game Over", 560, 140, 40, WHITE);
        DrawRectangleRec(same_btn, DARKBLUE);
        DrawText("Play Again", 560, 215, 25, WHITE);
        DrawRectangleRec(new_btn, DARKBLUE);
        DrawText("New Game", 550, 315, 25, WHITE);
        DrawRectangleRec(switch_btn, DARKBLUE);
        DrawText(is_ai?"Switch to PvP":"Switch to AI", 530, 415, 25, WHITE);
        DrawRectangleRec(main_btn, DARKBLUE);
        DrawText("Main Menu", 555, 515, 25, WHITE);

        EndDrawing();
    }
    return 0;
}
// user input
std::string getPlayerName(Player &p , const std::string& prompt) {
    std::string name="";

    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        int key=GetCharPressed();
        if(IsKeyPressed(KEY_ENTER) and !name.empty()){
            p.setName(name);
          break;
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
        EndDrawing();
    }
    return name;
}
void getPlayerSymbol(Player &p,std::string prompt)
 {
Rectangle x_btn={400,300,150,60};
Rectangle o_btn={600,300,150,60};
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, x_btn)) {
                p.setSymbol('X');
return;
            }
            if (CheckCollisionPointRec(mouse_pos, o_btn)) {
                p.setSymbol('O');
                return;
            }
        }
        BeginDrawing();
        ClearBackground({20,20,40,225});
        DrawText((prompt+" Choose Your Symbol:").c_str(), 380, 220, 25, WHITE);
        DrawRectangleRec(x_btn, DARKBLUE);
        DrawText("X", 460, 318, 30, RED);
        DrawRectangleRec(o_btn, DARKBLUE);
        DrawText("O", 660, 318, 30, GREEN);
        EndDrawing();
    }
}