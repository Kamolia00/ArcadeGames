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
        DrawText("Press P to pause/resume", 20, 50, 20, RED);

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