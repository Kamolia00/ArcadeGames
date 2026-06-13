#ifndef snake_h
#define snake_h
#include <iostream>
#include "raylib.h"
#include "deque"
#include "player stuff/player.h"
class Snake : public Player{
private:
std::deque<Vector2> body; // Deque to store the snake's body segments
bool isGrowing;
    Vector2 direction;

public:
    Snake();
    Snake(std::string name, char symbol);

    void move();
    void setDirection(Vector2 newDirection);
    void grow();
    void reset();

    bool checkSelfCollision() const;
    Vector2 getHead() const;
    const std::deque<Vector2>& getBody() const;
    Vector2 getDirection() const;

    void draw() const;
};
#endif
