#include "xo.h"
#include "raylib.h"
#include "connect4.h"
#include "valid_input.h"
#include "player.h"
#include <iostream>
using namespace std;
#include "raylib.h"

int main() {
Player p1("Player 1", 'X');
    Player p2("Player 2", 'O');
    XO game(p1, p2);
    game.playGameGUI();
}