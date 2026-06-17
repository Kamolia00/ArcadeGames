#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"
#include <algorithm>
#include "raylib.h"
#include "snake_game/main_game/menu_snake.h"
using namespace std;
std::map<std::string, int> SnakeGame::leaderboard_default;
std::map<std::string, int> SnakeGame::leaderboard_levels;
SnakeGame::SnakeGame(Snake &snake) : snake(snake),food({0, 0}) {
    spawnFood();
}
void SnakeGame::drawLeaderboard(const std::map<std::string, int>& board, int x, int y) {
    // sort by score descending
    std::vector<std::pair<std::string, int>> entries(board.begin(), board.end());
    std::sort(entries.begin(), entries.end(),
        [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) {
            return b.second < a.second;
        });

    DrawText("Leaderboard", x, y, 22, GOLD);
    int top = std::min((int)entries.size(), 5);
    for (int i = 0; i < top; i++) {
        const char* line = TextFormat("%d. %s - %d",
            i+1, entries[i].first.c_str(), entries[i].second);
        DrawText(line, x, y + 30 + i * 28, 20, WHITE);
    }
}
const std::map<std::string, int>& SnakeGame::getLeaderboard_default() const {
    return leaderboard_default;
}
const std::map<std::string, int>& SnakeGame::getLeaderboard_levels() const {
    return leaderboard_levels;
}
void SnakeGame::spawnFood() {
    bool spawned = false;
    while (!spawned) {
        food.x = rand() %GRID_WIDTH;
        food.y = rand() %GRID_HEIGHT;
        spawned = true;
        for (const auto &bodyPart : snake.getBody()) {
            if (bodyPart.x == food.x && bodyPart.y == food.y) {
                spawned = false;
                break;
            }
        }
        for (const auto &obstacle : obstacles) {
            if (obstacle.x == food.x && obstacle.y == food.y) {
                spawned = false;
                break;
            }
        }
    }
}
void SnakeGame::spawnObstacles(int count) {
    for (int i = 0; i < count; ++i) {
        Vector2 obstacle;
        bool spawned = false;
        while (!spawned) {
            obstacle.x = rand() %GRID_WIDTH;
            obstacle.y = rand() %GRID_HEIGHT;
            spawned = true;
            for (const auto &bodyPart : snake.getBody()) {
                if (bodyPart.x == obstacle.x && bodyPart.y == obstacle.y) {
                    spawned = false;
                    break;
                }
            }
            if (obstacle.x == food.x && obstacle.y == food.y) {
                spawned = false;
            }
            for (const auto &existing : obstacles) {
                if (existing.x == obstacle.x && existing.y == obstacle.y) {
                    spawned = false;
                    break;
                }
            }
        }
        obstacles.push_back(obstacle);
        if (obstacles.size() > 5) {
            obstacles.erase(obstacles.begin());
        }
    }
}

bool SnakeGame:: checkWallCollision() const {
    Vector2 head = snake.getHead();
    return head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT;
}
bool SnakeGame::checkObstacleCollision() const {
    Vector2 head = snake.getHead();
    for (const auto &obstacle : obstacles) {
        if (obstacle.x == head.x && obstacle.y == head.y) {
            return true;
        }
    }
    return false;
}
void SnakeGame::updateLeaderboard(std::map<std::string, int>& board,
                                   const std::string& name, int score) {
    if (board.find(name) == board.end() || score > board[name]) {
        board[name] = score;
    }
}
//Default_mode
int SnakeGame::Default_mode() {
    snake.reset();
    snake.setScore(0);
    obstacles.clear();
    spawnFood();
    double moveTimer = 0;
    double moveInterval = 0.15;
    double obstacleTimer = 0;
    bool gameOver = false;
    bool won = false;
    bool paused = false;

    // New: handle self-collision freeze so we can show where collision happened
    bool collisionFreeze = false;
    double collisionTimer = 0.0;
    Vector2 collisionPos = {0, 0};

    while (!WindowShouldClose() && !gameOver && !won) {
        if (IsKeyPressed(KEY_P)) paused = !paused;

        if (!paused) {
            // If we're in the short collision freeze, don't accept movement input or advance the snake
            if (!collisionFreeze) {
                if (IsKeyPressed(KEY_UP))    snake.setDirection({0, -1});
                if (IsKeyPressed(KEY_DOWN))  snake.setDirection({0, 1});
                if (IsKeyPressed(KEY_LEFT))  snake.setDirection({-1, 0});
                if (IsKeyPressed(KEY_RIGHT)) snake.setDirection({1, 0});

                moveTimer += GetFrameTime();
                if (moveTimer >= moveInterval) {
                    moveTimer = 0;

                    // compute where the head will be BEFORE moving so we can detect
                    // collisions with the current body including the tail that may be
                    // removed by move. This ensures running into the tail is
                    // treated as a collision and we can show where it happened.
                    Vector2 predictedHead = snake.getHead();
                    Vector2 dir = snake.getDirection();
                    predictedHead.x += dir.x;
                    predictedHead.y += dir.y;

                    bool selfCollBeforeMove = false;
                    for (const auto &seg : snake.getBody()) {
                        if (seg.x == predictedHead.x && seg.y == predictedHead.y) {
                            selfCollBeforeMove = true;
                            break;
                        }
                    }

                    // perform the move (this may pop the tail)
                    snake.move();

                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        snake.grow();
                        // apply multiplier for special player name "kamolia"
                        std::string pname = snake.getName();
                        std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
                        int mult = (pname == "kamolia") ? 5 : 1;
                        if (mult == 1) {
                            snake.incrementScore();
                        } else {
                            // add the multiplied points (replace default +1 with +mult)
                            snake.addScore(mult);
                        }
                        spawnFood();
                    }
                    int score = snake.getScore();
                    if (score >= 10) {
                        moveInterval = 0.10; // sped up once past 10
                    }

                    // handle collisions: wall/obstacle still end immediately, but
                    // self-collision (including running into the tail) will freeze
                    if (checkWallCollision() || checkObstacleCollision()) {
                        gameOver = true; // immediate end for wall/obstacle
                    } else if (selfCollBeforeMove || snake.checkSelfCollision()) {
                        // start a short freeze so player can see where the collision happened
                        collisionFreeze = true;
                        collisionTimer = 0.0;
                        collisionPos = predictedHead; // show the position where we hit
                    }

                    if (score >= 200) {
                        won = true;
                    }
                }
            } else {
                // we're frozen on self-collision: count down the timer then end the game
                collisionTimer += GetFrameTime();
                if (collisionTimer >= 1.0) { // wait 1 second
                    gameOver = true;
                }
            }

            // continuous obstacle spawning after score 10
            if (snake.getScore() >= 10) {
                obstacleTimer += GetFrameTime();
                if (obstacleTimer >= 3.0) { // every 3 seconds
                    obstacleTimer = 0;
                    spawnObstacles(1);
                }
            }
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});

        DrawText("Snake", WINDOW_WIDTH/2 - 60, 20, 40, WHITE);
         DrawText(TextFormat("Score: %d", snake.getScore()), 20, 20, 20, WHITE);
         DrawText("P = pause", WINDOW_WIDTH - 120, 20, 18, GRAY);
         DrawRectangleLines(OFFSET_X, OFFSET_Y, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, SKYBLUE);

        snake.draw(collisionFreeze, collisionPos);
        DrawRectangle(food.x * CELL_SIZE + OFFSET_X, food.y * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, YELLOW);

        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X, obs.y * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, WHITE);
        }

        // If we are in the self-collision freeze, highlight where it happened
        if (collisionFreeze) {
            int px = collisionPos.x * CELL_SIZE + OFFSET_X;
            int py = collisionPos.y * CELL_SIZE + OFFSET_Y;
            // draw a red box with an X to indicate collision
            DrawRectangleLines(px, py, CELL_SIZE, CELL_SIZE, RED);
            DrawLine(px, py, px + CELL_SIZE, py + CELL_SIZE, RED);
            DrawLine(px + CELL_SIZE, py, px, py + CELL_SIZE, RED);
        }

        if (paused && !collisionFreeze) {
            DrawText("PAUSED", WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2, 30, WHITE);
        }

        EndDrawing();
    }

    // post-game overlay message
    updateLeaderboard(leaderboard_default, snake.getName(), snake.getScore());
    int choice = showPostGame_menu(won, false, 0, leaderboard_default);
    return choice;
}
int SnakeGame::play_gui(int level) {
    Color bgColor;
    //set color
    switch (level) {
        case 1: bgColor = {20, 20, 40, 255}; break;
        case 2: bgColor = {20, 60, 20, 255}; break;
        case 3: bgColor = {60, 10, 10, 255}; break;
        default: bgColor = {20, 20, 40, 255};
    }
    double moveInterval = (level == 1) ? 0.15 : (level == 2) ? 0.10 : 0.07;
    int scorePerFood    = 5;
    int scoreToNext     = level * 50;
    Color obsColor      = (level == 3) ? ORANGE : SKYBLUE;

    obstacles.clear();
    if (level == 2) spawnObstacles(5);
    if (level == 3) spawnObstacles(8);

    snake.reset();
    snake.setScore(0);
    spawnFood();
// movement
    double moveTimer      = 0;
    double obstacleTimer  = 0;
    bool gameOver         = false;
    bool levelComplete    = false;
    bool paused           = false;
    bool collisionFreeze  = false;
    double collisionTimer = 0;
    Vector2 collisionPos  = {0, 0};

    while (!WindowShouldClose() && !gameOver && !levelComplete) {
        if (IsKeyPressed(KEY_P)) paused = !paused;

        if (!paused) {
            if (!collisionFreeze) {
                if (IsKeyPressed(KEY_UP))    snake.setDirection({0, -1});
                if (IsKeyPressed(KEY_DOWN))  snake.setDirection({0, 1});
                if (IsKeyPressed(KEY_LEFT))  snake.setDirection({-1, 0});
                if (IsKeyPressed(KEY_RIGHT)) snake.setDirection({1, 0});

                moveTimer += GetFrameTime();
                if (moveTimer >= moveInterval) {
                    moveTimer = 0;

                    // predict next head position to detect self-collision against
                    // the current body (including tail), so collisions into the
                    // tail are captured and can be highlighted.
                    Vector2 predictedHead = snake.getHead();
                    Vector2 dir = snake.getDirection();
                    predictedHead.x += dir.x;
                    predictedHead.y += dir.y;

                    bool selfCollBeforeMove = false;
                    for (const auto &seg : snake.getBody()) {
                        if (seg.x == predictedHead.x && seg.y == predictedHead.y) {
                            selfCollBeforeMove = true;
                            break;
                        }
                    }

                    snake.move();

                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        snake.grow();
                        // apply multiplier for special player name "kamolia"
                        std::string pname = snake.getName();
                        std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
                        int mult = (pname == "kamolia") ? 5 : 1;
                        snake.addScore(scorePerFood * mult);
                        spawnFood();
                    }

                    if (snake.getScore() >= scoreToNext)
                        levelComplete = true;

                    if (checkWallCollision() || checkObstacleCollision()) {
                        gameOver = true;
                    } else if (selfCollBeforeMove || snake.checkSelfCollision()) {
                        collisionFreeze = true;
                        collisionTimer  = 0.0;
                        collisionPos    = predictedHead;
                    }
                }

                if (level >= 2) {
                    obstacleTimer += GetFrameTime();
                    if (obstacleTimer >= 5.0) {
                        obstacleTimer = 0;
                        spawnObstacles(1);
                    }
                }

            } else {
                collisionTimer += GetFrameTime();
                if (collisionTimer >= 1.0) gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(bgColor);

        int titleW = MeasureText("Snake", 40);
         DrawText("Snake", WINDOW_WIDTH/2 - titleW/2, 20, 40, WHITE);
         DrawText(TextFormat("Score: %d", snake.getScore()), 20, 20, 20, WHITE);
         DrawText(TextFormat("Level: %d  |  Next: %d", level, scoreToNext), 20, 45, 18, GRAY);
         DrawText("P = pause", WINDOW_WIDTH - 120, 20, 18, GRAY);

        DrawRectangleLines(OFFSET_X, OFFSET_Y,
            GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, SKYBLUE);

        snake.draw(collisionFreeze, collisionPos);

        DrawRectangle(
            food.x * CELL_SIZE + OFFSET_X,
            food.y * CELL_SIZE + OFFSET_Y,
            CELL_SIZE, CELL_SIZE, YELLOW);

        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X,
                obs.y * CELL_SIZE + OFFSET_Y,
                CELL_SIZE, CELL_SIZE, obsColor);
            DrawRectangleLines(obs.x * CELL_SIZE + OFFSET_X,
                obs.y * CELL_SIZE + OFFSET_Y,
                CELL_SIZE, CELL_SIZE, WHITE);
        }

        if (collisionFreeze) {
            int px = collisionPos.x * CELL_SIZE + OFFSET_X;
            int py = collisionPos.y * CELL_SIZE + OFFSET_Y;
            DrawRectangle(px, py, CELL_SIZE, CELL_SIZE, {255, 0, 0, 150});
            DrawRectangleLines(px, py, CELL_SIZE, CELL_SIZE, RED);
            DrawLine(px, py, px+CELL_SIZE, py+CELL_SIZE, RED);
            DrawLine(px+CELL_SIZE, py, px, py+CELL_SIZE, RED);
            int msgW = MeasureText("SELF COLLISION!", 20);
            DrawText("SELF COLLISION!", WINDOW_WIDTH/2 - msgW/2, OFFSET_Y - 30, 20, RED);
        }

        if (paused && !collisionFreeze) {
            int pw = MeasureText("PAUSED", 30);
            DrawText("PAUSED", WINDOW_WIDTH/2 - pw/2, WINDOW_HEIGHT/2, 30, WHITE);
        }

        EndDrawing();
    }

    // end screen
    updateLeaderboard(leaderboard_levels, snake.getName(), snake.getScore());
    int choice = showPostGame_menu(false, levelComplete, level, leaderboard_levels);
    if (levelComplete && level < 3 && choice == 1) return 1;
    return choice == 1 ? -1 : 0;
}