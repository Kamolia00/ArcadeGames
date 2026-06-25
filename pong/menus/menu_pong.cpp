#include"pong/menus/menu_pong.h"
int showmenu_pong() {
    BeginDrawing(); EndDrawing();
    Rectangle pvp={490,250,300,60};
    Rectangle ai={490,350,300,60};
    Rectangle exit={490,450,300,60};
    while (!WindowShouldClose()) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos,pvp))
                return 1;
            if (CheckCollisionPointRec(mousePos,ai))
                return 2;
            if (CheckCollisionPointRec(mousePos,exit))
                return 0;
        }
        BeginDrawing();
         ClearBackground({20,20,40,225});
        DrawText("Pong Game",520,140,40,WHITE);
         DrawRectangleRec(pvp,DARKBLUE);
         int pvpW = MeasureText("Player vs Player", 25);
         DrawText("Player vs Player",
                      pvp.x + (pvp.width - pvpW) / 2,
                      pvp.y + (pvp.height - 25) / 2, 25, WHITE);
         DrawRectangleRec(ai,DARKBLUE);
         int aiW = MeasureText("Player vs AI", 25);
         DrawText("Player vs AI",
                      ai.x + (ai.width - aiW) / 2,
                      ai.y + (ai.height - 25) / 2, 25, WHITE);
         DrawRectangleRec(exit,DARKBLUE);
         int exW = MeasureText("Exit", 25);
        DrawText("Exit",
                      exit.x + (exit.width - exW) / 2,
                      exit.y + (exit.height - 25) / 2, 25, WHITE);
        EndDrawing();
    }
    return 0;
}
bool getPlayerName_pong(Player &p, const std::string prompt) {
    std::string name = "";
    Rectangle back_btn = {490, 450, 300, 60};
    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER) && !name.empty()) {
            p.setName(name);
            return true;
        }
        if (IsKeyPressed(KEY_ESCAPE)) return false;
        int key = GetCharPressed();
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, back_btn)) {
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) name.pop_back();
        if (key >= 32 && key <= 125) name += (char)key;

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText(prompt.c_str(), 400, 220, 25, SKYBLUE);
        DrawText("Enter Your Name:", 400, 280, 25, WHITE);
        DrawText(name.c_str(), 400, 320, 25, YELLOW);
        DrawText("Press Enter to Continue", 400, 370, 20, GRAY);
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("Back", 25);
        DrawText("Back",
            back_btn.x + (back_btn.width - backW)/2,
            back_btn.y + (back_btn.height - 25)/2, 25, WHITE);
        EndDrawing();
    }
    return false;
}
int showPostGame_menu_pong(Player p1,Player p2, int g1,int g2) {
    Rectangle again_btn = {490, 260, 300, 60};
    Rectangle back_btn = {490, 340, 300, 60};
BeginDrawing();
EndDrawing();
while (!WindowShouldClose()) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, again_btn))
            return 2;
        if (CheckCollisionPointRec(mousePos, back_btn))
            return 1;
    }
BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    DrawText("Game Over", 560, 140, 40, WHITE);
        DrawText((p1.getName() + ": " + std::to_string(g1)).c_str(), 490, 180, 25, YELLOW);
        DrawText((p2.getName() + ": " + std::to_string(g2)).c_str(), 490, 220, 25, YELLOW);
   DrawRectangleRec(again_btn, DARKBLUE);
    int sameW = MeasureText("Play Again", 25);
    DrawText("Play Again",
             again_btn.x + (again_btn.width - sameW) / 2,
             again_btn.y + (again_btn.height - 25) / 2, 25, WHITE);
    DrawRectangleRec(back_btn, DARKBLUE);
    int backW = MeasureText("Main Menu ", 25);
    DrawText("Main Menu ",
             back_btn.x + (back_btn.width - backW) / 2,
             back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);
EndDrawing();
}
    return 0;
}
bool getPlayerColor_pong(Player &p) {
    Rectangle green_btn = {260, 300, 150, 60};
    Rectangle red_btn   = {440, 300, 150, 60};
    Rectangle blue_btn  = {620, 300, 150, 60};
    Rectangle white  = {800, 300, 150, 60};
    Rectangle back_btn  = {490, 450, 300, 60};
    int selected = -1; // no color initially selected

    // wait one frame to clear previous input state
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) {
            p.setSymbol('g');
            return true;
        }
        if (IsKeyPressed(KEY_TWO)) {
            p.setSymbol('r');
            return true;
        }
        if (IsKeyPressed(KEY_THREE)) {
            p.setSymbol('b');
            return true;
        }
        if (IsKeyPressed(KEY_FOUR)) {
            p.setSymbol('w');
            return true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, green_btn)) {
                p.setSymbol('g');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, red_btn)) {
                p.setSymbol('r');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, blue_btn)) {
                p.setSymbol('b');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, white)) {
                p.setSymbol('w');
                BeginDrawing(); EndDrawing();
                return true;
            }
            if (CheckCollisionPointRec(mouse_pos, back_btn)) {
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        Vector2 mouse_pos = GetMousePosition();
        selected = -1;
        if (CheckCollisionPointRec(mouse_pos, green_btn)) selected = 0;
        else if (CheckCollisionPointRec(mouse_pos, red_btn)) selected = 1;
        else if (CheckCollisionPointRec(mouse_pos, blue_btn)) selected = 2;
        else if (CheckCollisionPointRec(mouse_pos, white)) selected = 3;
        BeginDrawing();
        ClearBackground({20,20,40,225});
        DrawText((p.getName() + " Choose Your Color:").c_str(), 420, 220, 25, WHITE);
        DrawText("(or press 1-4, or ESC to go back)", 420, 250, 18, GRAY);

        DrawRectangleRec(green_btn, selected == 0 ? Color{50, 150, 200, 255} : DARKBLUE);
        int gW = MeasureText("GREEN", 30);
        DrawText("GREEN",
                 green_btn.x + (green_btn.width - gW) / 2,
                 green_btn.y + (green_btn.height - 30) / 2, 30, GREEN);

        DrawRectangleRec(red_btn, selected == 1 ? Color{50, 150, 200, 255} : DARKBLUE);
        int rW = MeasureText("RED", 30);
        DrawText("RED",
                 red_btn.x + (red_btn.width - rW) / 2,
                 red_btn.y + (red_btn.height - 30) / 2, 30, RED);

        DrawRectangleRec(blue_btn, selected == 2 ? Color{50, 150, 200, 255} : DARKBLUE);
        int bW = MeasureText("BLUE", 30);
        DrawText("BLUE",
                 blue_btn.x + (blue_btn.width - bW) / 2,
                 blue_btn.y + (blue_btn.height - 30) / 2, 30, BLUE);

        DrawRectangleRec(white, selected == 3 ? Color{50, 150, 200, 255} : DARKBLUE);
        int dW = MeasureText("WHITE", 24);
        DrawText("WHITE",
                 white.x + (white.width - dW) / 2,
                 white.y + (white.height - 24) / 2, 24, WHITE);

        // Back button
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("Back", 25);
        DrawText("Back",
                 back_btn.x + (back_btn.width - backW) / 2,
                 back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);

        EndDrawing();
    }
    // window closed without choosing -> treat as cancel
    return false;
}

int setThreshold_pong() {
    std::string input = "";
    std::string error = "";
    Rectangle back_btn = {490, 450, 300, 60};
    BeginDrawing(); EndDrawing();

    while (!WindowShouldClose()) {
        int key = GetCharPressed();

        if (IsKeyPressed(KEY_ENTER)) {
            if (input.empty()) {
                error = "Please enter a number!";
            } else {
                int val = std::stoi(input);
                if (val < 1 || val > 8) {
                    error = "Enter a number between 1 and 8!";
                    input = "";
                } else {
                    return val;
                }
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) {
            input.pop_back();
            error = "";
        }
        if (key >= '1' && key <= '9' && input.size() < 1) {
            input += (char)key;
            error = "";
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, back_btn)) {
                BeginDrawing(); EndDrawing();
                return -1; // cancelled
            }
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Set Score Limit", 490, 140, 35, WHITE);
        DrawText("Enter max score (1-8):", 490, 220, 25, WHITE);
        DrawText(input.c_str(), 490, 270, 40, YELLOW);
        if (!error.empty()) {
            DrawText(error.c_str(), 490, 330, 20, RED);
        }
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("Back", 25);
        DrawText("Back",
            back_btn.x + (back_btn.width - backW)/2,
            back_btn.y + (back_btn.height - 25)/2, 25, WHITE);
        EndDrawing();
    }
    return -1;
}
