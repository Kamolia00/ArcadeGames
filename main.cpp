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

  while (true) {
   Player p1, p2, ai;
   ai.setName("AI");
   const int choice = showmenu();
      if (choice==0 or WindowShouldClose())
          break;
      if (choice==1) {
          getPlayerName(p1,"Player 1");
          getPlayerName(p2,"Player 2");
getPlayerSymbol(p1,p1.getName() + " choose your symbol");
          p2.setSymbol(p1.getSymbol()=='X'?'O':'X');

          while (true) {
XO game(p1,p2);
    game.playGameGUI_pvp();
              if(WindowShouldClose()) break;  // add here
              const int after= showPostGameMenu(p1,p2);
              if (after==0 or after==-1)break;
              // after == 1: play again, loop
          }
          if (WindowShouldClose())break;
      }else if (choice==2) {
          getPlayerName(p1,"Player 1");
getPlayerSymbol(p1,p1.getName() + " choose your symbol");
          ai.setSymbol(p1.getSymbol()=='X'?'O':'X');
          int difficulty=showAiMenu();
          if(difficulty == 0 || WindowShouldClose()) continue;
          while(true){
              XO game(p1, ai);
              if(difficulty == 1) game.playGameGUI_ai_easy();
              else game.playGameGUI_ai_hard();
              if(WindowShouldClose()) break;  // add here
              const int after = showPostGameMenu(p1,ai);
              if(after == 0 or after==-1) break;  // main menu
          }
      }
      if(WindowShouldClose()) break;
  }
    CloseWindow();
   return 0;
}