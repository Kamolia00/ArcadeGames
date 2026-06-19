#ifndef BALL_H
#define BALL_H
#include "raylib.h"
class Ball {
private:
    float x,y;
    int speed_x,speed_y;
    int radius;
public:
    void draw();
    Ball(float x, float y, int speed_x, int speed_y, int radius);
    void setPosition(float x, float y);
    void setSpeed(int speed_x, int speed_y);
    void setRadius(int radius);
    float getX() ;
    float getY() ;
    int getSpeedX() ;
    int getSpeedY() ;
    int getRadius() ;
    void update();
};
#endif