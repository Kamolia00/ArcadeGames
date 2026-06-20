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
}