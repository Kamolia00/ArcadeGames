#ifndef PONG_H
#define PONG_H
#include "pong/pong game/ball.h"
#include "player stuff/player.h"
#include "raylib.h"
class Pong {
    private:
    Player p1;
    Player p2;
    Player ai;
    int threshold{};
    int gamesP1=0;
    int gamesP2=0;
    int aiWins=0;
    Rectangle paddle1Rect{};
    Rectangle paddle2Rect{};
    Rectangle aiRect{};
    Ball ball;
    void movePaddel1();
    void movePaddel2();
    void moveAi();
public:
    int getGamesP1() const;
    int getGamesP2() const;
    int getAiWins() const;
        void setThreshold(int n);
        Pong(const Player &p1, const Player &p2, const Ball &ball, const int threshold);
        void playGame_pvp();
        void playGame_ai();
};
#endif
