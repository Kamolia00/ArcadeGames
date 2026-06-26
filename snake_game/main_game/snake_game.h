#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "snake_game/snake/snake.h"
#include <vector>
#include <map>
#include <string>
class SnakeGame {
private:
static std::map<std::string, int> leaderboard_default;
    bool muted_sfx = false;
    Sound sfx_food;
    Sound sfx_collision;
    Sound sfx_move;
    static std::map<std::string, int> leaderboard_levels;
    Snake &snake;
    Vector2 food;
    std::vector<Vector2> obstacles;
    void drawLeaderboard(const std::map<std::string, int>& board, int x, int y);
const std::map<std::string, int>& getLeaderboard_default() const;
    const std::map<std::string, int>& getLeaderboard_levels() const;
    void spawnFood();
    void spawnObstacles(int count) ;
    bool checkWallCollision() const;
   bool checkObstacleCollision() const;
    void updateLeaderboard(std::map<std::string, int>& board,
                       const std::string& name, int score);
public:
    ~SnakeGame();
    SnakeGame(Snake &snake);
 int Default_mode();
    int play_gui(int level);
};
#endif