#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"

#include "raylib.h"
using namespace std;
SnakeGame::SnakeGame(Snake &snake) : snake(snake),food({0, 0}) {
    spawnFood();
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
//Default_mode
void SnakeGame::Default_mode() {
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
                    snake.move();

                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        snake.grow();
                        snake.incrementScore();
                        spawnFood();
                    }

                    int score = snake.getScore();
                    if (score >= 10) {
                        moveInterval = 0.10; // sped up once past 10
                    }

                    // handle collisions: wall/obstacle still end immediately, but self-collision will freeze
                    if (checkWallCollision() || checkObstacleCollision()) {
                        gameOver = true; // immediate end for wall/obstacle
                    } else if (snake.checkSelfCollision()) {
                        // start a short freeze so player can see where the collision happened
                        collisionFreeze = true;
                        collisionTimer = 0.0;
                        collisionPos = snake.getHead();
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

        snake.draw();
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

    // post-game: freeze final state, overlay message
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});

        DrawText("Snake", WINDOW_WIDTH/2 - 60, 20, 40, WHITE);
        DrawText(TextFormat("Score: %d", snake.getScore()), 20, 20, 20, WHITE);
        DrawRectangleLines(OFFSET_X, OFFSET_Y, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, SKYBLUE);

        snake.draw();
        DrawRectangle(food.x * CELL_SIZE + OFFSET_X, food.y * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, YELLOW);
        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X, obs.y * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, BLACK);
        }

        // overlay
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0, 150}); // semi-transparent dim
        DrawText(won ? "You Win!" : "Game Over", WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 40, 40, won ? GOLD : RED);
        DrawText("Press ENTER to continue", WINDOW_WIDTH/2 - 130, WINDOW_HEIGHT/2 + 20, 20, WHITE);

        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) break;
    }
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
                    snake.move();

                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        snake.grow();
                        snake.addScore(scorePerFood);
                        spawnFood();
                    }

                    if (snake.getScore() >= scoreToNext)
                        levelComplete = true;

                    if (checkWallCollision() || checkObstacleCollision()) {
                        gameOver = true;
                    } else if (snake.checkSelfCollision()) {
                        collisionFreeze = true;
                        collisionTimer  = 0.0;
                        collisionPos    = snake.getHead();
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

        snake.draw();

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
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bgColor);

        DrawRectangleLines(OFFSET_X, OFFSET_Y,
            GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, SKYBLUE);
        snake.draw();
        DrawRectangle(
            food.x * CELL_SIZE + OFFSET_X,
            food.y * CELL_SIZE + OFFSET_Y,
            CELL_SIZE, CELL_SIZE, YELLOW);
        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X,
                obs.y * CELL_SIZE + OFFSET_Y,
                CELL_SIZE, CELL_SIZE, obsColor);
        }

        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0, 180});

        if (levelComplete) {
            const char* msg = (level < 3)
                ? TextFormat("Level %d Complete!", level)
                : "You Beat All Levels!";
            int msgW = MeasureText(msg, 35);
            DrawText(msg, WINDOW_WIDTH/2 - msgW/2, WINDOW_HEIGHT/2 - 60, 35, GOLD);
            const char* next = (level < 3)
                ? TextFormat("Press ENTER for Level %d", level + 1)
                : "Press ENTER to finish";
            int nextW = MeasureText(next, 22);
            DrawText(next, WINDOW_WIDTH/2 - nextW/2, WINDOW_HEIGHT/2, 22, WHITE);
        } else {
            int goW = MeasureText("Game Over", 40);
            DrawText("Game Over", WINDOW_WIDTH/2 - goW/2, WINDOW_HEIGHT/2 - 60, 40, RED);
            int exitW = MeasureText("Press ENTER to exit", 22);
            DrawText("Press ENTER to exit", WINDOW_WIDTH/2 - exitW/2, WINDOW_HEIGHT/2, 22, WHITE);
        }

        DrawText(TextFormat("Score: %d", snake.getScore()),
            WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2 + 50, 25, WHITE);

        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) break;
    }

    return levelComplete ? 1 : 0;
}