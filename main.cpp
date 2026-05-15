#include"xo.h"
int main() {
Player p1,p2;
    p1.setName("kamal");
    p1.setSymbol('X');
    p2.setSymbol('O');
    p2.setName("ai");
    XO game=XO(p1,p2);
    game.vsai_easy();
}