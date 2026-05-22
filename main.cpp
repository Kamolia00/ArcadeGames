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
      // player's info
   Player p1, p2, ai;
   ai.setName("AI");
   const int choice = showmenu();
//exit
      if (choice==0 or WindowShouldClose())
          break;
      //game is on
      // pvp block

      if (choice==1) {
          //info
          // if user clicks Back / presses ESC during start go back to the main menu
          if(!getPlayerName(p1,"Player 1")) { if(WindowShouldClose()) break; continue; }
          // same
          if(!getPlayerName(p2,"Player 2")) { if(WindowShouldClose()) break; continue; }
          // same handling for the symbol picker
          if(!getPlayerSymbol(p1,p1.getName() + " choose your symbol")) { if(WindowShouldClose()) break; continue; }
          p2.setSymbol(p1.getSymbol()=='X'?'O':'X');
//game start pvp
          while (true) {
XO game(p1,p2);
    game.playGameGUI_pvp();
              if(WindowShouldClose()) break;  //force stop
              const int after= showPostGameMenu(p1,p2);
              // force close in the middle of the game (1)
              if (after==0 or after==-1)break;
              // after == 1: play again, loop
              if(WindowShouldClose()) break;
          }
          //(1)
          if (WindowShouldClose())break;
      // AI game on
      }else if (choice==2) {
          //info
          // if user clicks Back or exit
          if(!getPlayerName(p1,"Player 1")) { if(WindowShouldClose()) break; continue; }
          // same Back handling for the symbol picker
          if(!getPlayerSymbol(p1,p1.getName() + " choose your symbol")) { if(WindowShouldClose()) break; continue; }
          ai.setSymbol(p1.getSymbol()=='X'?'O':'X');
          int difficulty=showAiMenu();
          //force close
          if(difficulty == 0 || WindowShouldClose()) continue;
          while(true){
              // game is on AI
              XO game(p1, ai);
              if(difficulty == 1) game.playGameGUI_ai_easy();
              else game.playGameGUI_ai_hard();
              //force close
              if(WindowShouldClose()) break;
              const int after = showPostGameMenu(p1,ai);
              if(after == 0 or after==-1) break;  // main menu
          }
      }
      if(WindowShouldClose()) break;
  }
    CloseWindow();
   return 0;
}