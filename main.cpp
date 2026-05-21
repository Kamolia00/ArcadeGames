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

   Player p1, p2, ai;
   ai.setName("AI");
   int choice = showmenu();
   if(choice == 1){
      getPlayerName(p1, "Player 1");
      getPlayerName(p2, "Player 2");
      getPlayerSymbol(p1,p1.getName());

      p2.setSymbol(p1.getSymbol()=='X'?'O':'X');
      if (p1.getSymbol()=='X') {
         XO game(p1, p2);
         game.playGameGUI_pvp();
      }else {
   XO game(p2, p1);
   game.playGameGUI_pvp();
         }
   }
   else if(choice == 2){
      getPlayerName(p1, "Player 1");

      getPlayerSymbol(p1,"PLayer 1");

      ai.setSymbol(p1.getSymbol()=='X'?'O':'X');
      int difficulty = showAiMenu();
      XO game(p1, ai);
      if(difficulty == 1) game.playGameGUI_ai_easy();
      else if(difficulty == 2) game.playGameGUI_ai_hard();
   }
   CloseWindow();
   return 0;
}