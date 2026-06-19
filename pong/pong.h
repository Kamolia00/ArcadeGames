#ifndef PONG_H
#define PONG_H
#include "pong/ball.h"
#include "player stuff/player.h"
#include "raylib.h"
class Pong {
    private:
    Player p1;
    Player p2;
    Player ai;
    int threshold{};
    int gamesP1,gamesP2;
    int aiWins;
    Rectangle paddle1Rect{};
    Rectangle paddle2Rect{};
    Rectangle aiRect{};
    Ball ball;
    void movePaddel1();
    void movePaddel2();
    void moveAi();
    void resetRound();
public:
        void setThreshold(int n);
        Pong(const Player &p1, const Player &p2, const Ball &ball, const int threshold);
        void playGame_pvp();
        void playGame_ai();
};
#endif
