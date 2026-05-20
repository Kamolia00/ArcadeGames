#include <iostream>
#include "player.h"
#include "xo.h"
#include "menuXo.h"

Font font;
int main() {
   InitWindow(1280, 720, "Arcade Games");
   SetTargetFPS(60);
   //custom font
   font = LoadFont("C:/Windows/Fonts/arial.ttf");

   Player p1("Player 1", 'X');
   Player p2("Player 2", 'O');
   Player ai("ai", 'O');

   int choice = showmenu();
   if(choice == 1){
      XO game(p1, p2);
      game.playGameGUI_pvp();
   }
   else if(choice == 2){
      int difficulty = showAiMenu();
      XO game(p1, ai);
      if(difficulty == 1) game.playGameGUI_ai_easy();
      else if(difficulty == 2) game.playGameGUI_ai_hard();
   }
   CloseWindow();
   return 0;
}