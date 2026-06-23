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
bool getPlayerName_pong(Player &p) {
    std::string name="";
    Rectangle back_btn={490,450,300,60};
    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_ENTER) and !name.empty()){
            p.setName(name);
            // signal success to caller
            return true;
        }
        if(IsKeyPressed(KEY_ESCAPE)) return false;
        int key=GetCharPressed();
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            Vector2 mouse_pos = GetMousePosition();
            if(CheckCollisionPointRec(mouse_pos, back_btn)) {
                // consume the input for one frame so the main menu does not
                // immediately receive the same mouse release (which shares
                // the same button/position) and inadvertently act on it.
                BeginDrawing(); EndDrawing();
                return false;
            }
        }
        if(IsKeyPressed(KEY_BACKSPACE) and !name.empty()){
            name.pop_back();
        }
        if(key >= 32 && key <= 125) name += (char)key;
        BeginDrawing();
        ClearBackground({20,20,40,225});
        DrawText(("Enter Your Name:"), 400, 280, 25, WHITE);
        DrawText(name.c_str(), 400, 320, 25, WHITE);
        DrawText("Press Enter to Continue", 400, 380, 20, WHITE);
        // draw the Back button
        DrawRectangleRec(back_btn, DARKBLUE);
        int backW = MeasureText("Back", 25);
        DrawText("Back",
                 back_btn.x + (back_btn.width - backW) / 2,
                 back_btn.y + (back_btn.height - 25) / 2, 25, WHITE);
EndDrawing();
    }
    return false;
}
int showPostGame_menu_pong(Player p1,Player p2, int g1,int g2) {
    Rectangle same_btn = {490, 260, 300, 60};
    Rectangle main_btn = {490, 340, 300, 60};

}