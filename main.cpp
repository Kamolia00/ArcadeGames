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
  while (true) {
   int choice = showmenu();
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
              int after= showPostGameMenu(false);
              if (after==0 or after==-1)break;
              else if (after==2) {
                  getPlayerName(p1, "Player 1");
                  getPlayerName(p2, "Player 2");
                  getPlayerSymbol(p1, "Player 1");
                  p2.setSymbol(p1.getSymbol()=='X'?'O':'X');
              }
              else if(after == 3){  // switch to AI
                  choice = 2;
                  break;
              }
              // after == 1: play again, loop
          }
          if (WindowShouldClose())break;
          if (choice==2) goto AI_MODE;
      }
      AI_MODE:
      if (choice==2) {
          getPlayerName(p1,"Player 1");
getPlayerSymbol(p1,p1.getName() + " choose your symbol");
          ai.setSymbol(p1.getSymbol()=='X'?'O':'X');
          int difficulty=showAiMenu();
          while(true){
              XO game(p1, ai);
              if(difficulty == 1) game.playGameGUI_ai_easy();
              else game.playGameGUI_ai_hard();
              if(WindowShouldClose()) break;  // add here
              int after = showPostGameMenu(true);
              if(after == 0 or after==-1) break;  // main menu
              else if(after == 2){   // new players
                  getPlayerName(p1, "Player 1");
                  getPlayerSymbol(p1, "Player 1");
                  ai.setSymbol(p1.getSymbol()=='X'?'O':'X');
                  difficulty = showAiMenu();
              }
              else if(after == 3) break;  // switch to PvP, back to main menu loop
              // after == 1: play again
          }
      }
      if(WindowShouldClose()) break;
  }
    CloseWindow();
   return 0;
}