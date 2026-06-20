#include "ball.h"
Ball::Ball(float x, float y, int speed_x, int speed_y, int radius){
    this->x = x;
    this->y = y;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->radius = radius;
}
void Ball::draw(){
    DrawCircle((int)x,(int)y,radius,RED);
}
void Ball::update(){
    x += speed_x;
    y += speed_y;
    if (y+radius >= GetScreenHeight() || y-radius <= 0 )
        speed_y *= -1;
   
}
void Ball::setPosition(float x, float y){
    this->x = x;
    this->y = y;
}
void Ball::setSpeed(int speed_x, int speed_y){
    this->speed_x = speed_x;
    this->speed_y = speed_y;
}
void Ball::setRadius(int radius){
    this->radius = radius;
}
float Ball::getX(){
    return x;
}
float Ball::getY(){
    return y;
}
int Ball::getSpeedX(){
    return speed_x;
}
int Ball::getSpeedY(){
    return speed_y;
}
int Ball::getRadius(){
    return radius;
}