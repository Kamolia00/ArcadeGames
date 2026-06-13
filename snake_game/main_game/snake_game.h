#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "snake_game/snake/snake.h"
#include <vector>
class SnakeGame {
private:
    Snake &snake;
    Vector2 food;
    std::vector<Vector2> obstacles;

    void spawnFood();
    void spawnObstacles(int count) ;
    bool checkWallCollision() const;
   bool checkObstacleCollision() const;
public:
    SnakeGame(Snake &snake);
    void Default_mode();
};
#endif