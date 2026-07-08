#include "snake_game/main_game/snake_game.h"
#include "snake_game/snake/constants.h"
#include <algorithm>
#include "raylib.h"
#include "snake_game/main_game/menu_snake.h"
using namespace std;
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;

extern Rectangle sfx_btn;
std::map<std::string, int> SnakeGame::leaderboard_default;
std::map<std::string, int> SnakeGame::leaderboard_levels;
SnakeGame::SnakeGame(Snake &snake) : snake(snake),food({0, 0}) {
    spawnFood();
    sfx_food = LoadSound("assets/sounds/eat.ogg");
    sfx_collision = LoadSound("assets/sounds/wall.ogg");
    if (!IsSoundValid(sfx_food)) {
    TraceLog(LOG_WARNING, "sfx_food failed to load!");
    }
    if (!IsSoundValid(sfx_collision)) {
    TraceLog(LOG_WARNING, "sfx_collision failed to load!");
        }
}
SnakeGame::~SnakeGame() {
    UnloadSound(sfx_food);
    UnloadSound(sfx_collision);
}
bool SnakeGame::checkSelfCollision() const {
    std::deque<Vector2> body = snake.getBody();
    Vector2 head = body.back();
    body.pop_back();

    for (const auto &seg : body) {
        if (seg.x == head.x && seg.y == head.y) return true;
    }
    return false;
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
    bool allowMove = true;
    bool gameOver = false;
    bool won = false;
    bool paused = false;
    bool collisionFreeze = false;
    double collisionTimer = 0.0;

    while (!WindowShouldClose() && !gameOver && !won) {
        if (IsKeyPressed(KEY_P)) paused = !paused;

        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, sfx_btn))  muted_sfx = !muted_sfx;
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm  = !mutedBGm;
        }

        if (!paused) {
            if (!collisionFreeze) {
                bool moved = false;
                if (allowMove) {
                    if (IsKeyPressed(KEY_UP) or IsKeyPressed(KEY_W))    { snake.setDirection({0, -1}); moved = true; }
                    if (IsKeyPressed(KEY_DOWN) or IsKeyPressed(KEY_S))  { snake.setDirection({0,  1}); moved = true; }
                    if (IsKeyPressed(KEY_LEFT) or IsKeyPressed(KEY_A))  { snake.setDirection({-1, 0}); moved = true; }
                    if (IsKeyPressed(KEY_RIGHT) or IsKeyPressed(KEY_D)) { snake.setDirection({1,  0}); moved = true; }
                    if (moved) allowMove = false;
                }

                moveTimer += GetFrameTime();
                if (moveTimer >= moveInterval) {
                    moveTimer = 0;
                    allowMove = true;

                    snake.move();

                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        if (!muted_sfx) PlaySound(sfx_food);
                        snake.grow();
                        std::string pname = snake.getName();
                        std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
                        int mult = (pname == "kamolia") ? 5 : 1;
                        if (mult == 1) snake.incrementScore();
                        else snake.addScore(mult);
                        spawnFood();
                    }

                    int score = snake.getScore();
                    if (score >= 10) moveInterval = 0.10;

                    if (checkWallCollision() || checkObstacleCollision() || checkSelfCollision()) {
                        if (!muted_sfx) PlaySound(sfx_collision);
                        collisionFreeze = true;
                        collisionTimer = 0.0;
                    }

                    if (score >= 200) won = true;
                }

                if (snake.getScore() >= 10) {
                    obstacleTimer += GetFrameTime();
                    if (obstacleTimer >= 3.0) {
                        obstacleTimer = 0;
                        spawnObstacles(1);
                    }
                }

            } else {
                collisionTimer += GetFrameTime();
                if (collisionTimer >= 2.0) gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground({20, 20, 40, 255});
        DrawText("Snake", WINDOW_WIDTH/2 - 60, 20, 40, WHITE);
        DrawText(TextFormat("Score: %d", snake.getScore()), 20, 20, 20, WHITE);
        DrawText("P = pause", WINDOW_WIDTH - 120, 20, 18, GRAY);

        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE",
            mute_btn.x + (mute_btn.width - muteW)/2,
            mute_btn.y + (mute_btn.height - 20)/2, 20,
            mutedBGm ? GREEN : RED);

        DrawRectangleRec(sfx_btn, DARKBLUE);
        const char* sfxLabel = muted_sfx ? "SFX ON" : "SFX OFF";
        int sfxW = MeasureText(sfxLabel, 20);
        DrawText(sfxLabel,
            sfx_btn.x + (sfx_btn.width - sfxW)/2,
            sfx_btn.y + (sfx_btn.height - 20)/2, 20,
            muted_sfx ? GREEN : RED);

        Color cellA = {26, 26, 52, 255};
Color cellB = {18, 18, 38, 255};
        for (int gy = 0; gy < GRID_HEIGHT; gy++) {
            for (int gx = 0; gx < GRID_WIDTH; gx++) {
                Color c = ((gx + gy) % 2 == 0) ? cellA : cellB;
                DrawRectangle(gx * CELL_SIZE + OFFSET_X, gy * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, c);
            }
        }
        snake.draw(collisionFreeze, snake.getHead());
        float fcx = food.x * CELL_SIZE + OFFSET_X + CELL_SIZE / 2.0f;
        float fcy = food.y * CELL_SIZE + OFFSET_Y + CELL_SIZE / 2.0f;
        float armLen = CELL_SIZE * 0.35f;
        float thick  = CELL_SIZE * 0.15f;
        DrawRectangle(fcx - armLen, fcy - thick/2, armLen*2, thick,  YELLOW);
        DrawRectangle(fcx - thick/2, fcy - armLen, thick, armLen*2,  YELLOW);        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X, obs.y * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, WHITE);
        }

        if (collisionFreeze) {
            Vector2 head = snake.getHead();
            int px = head.x * CELL_SIZE + OFFSET_X;
            int py = head.y * CELL_SIZE + OFFSET_Y;
            DrawRectangleLines(px, py, CELL_SIZE, CELL_SIZE, RED);
            DrawLine(px, py, px + CELL_SIZE, py + CELL_SIZE, RED);
            DrawLine(px + CELL_SIZE, py, px, py + CELL_SIZE, RED);
        }
        if (paused && !collisionFreeze) {
            DrawText("PAUSED", WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2, 30, WHITE);
        }
        EndDrawing();
    }

    if (WindowShouldClose()) return 0;
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
    bool allowMove = true;
    double collisionTimer = 0;
    Vector2 collisionPos  = {0, 0};

    while (!WindowShouldClose() && !gameOver && !levelComplete) {
        if (IsKeyPressed(KEY_P)) paused = !paused;
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, sfx_btn))  muted_sfx = !muted_sfx;
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm  = !mutedBGm;
        }

        if (!paused) {
            if (!collisionFreeze) {
                bool moved = false;

                if (allowMove) {
                    if (IsKeyPressed(KEY_UP) or IsKeyPressed(KEY_W)) {
                        snake.setDirection({0, -1});
                        moved = true;
                    }

                    if (IsKeyPressed(KEY_DOWN) or IsKeyPressed(KEY_S)) {
                        snake.setDirection({0, 1});
                        moved = true;
                    }

                    if (IsKeyPressed(KEY_LEFT) or IsKeyPressed(KEY_A)) {
                        snake.setDirection({-1, 0});
                        moved = true;
                    }

                    if (IsKeyPressed(KEY_RIGHT) or IsKeyPressed(KEY_D)) {
                        snake.setDirection({1, 0});
                        moved = true;
                    }

                    if (moved)
                        allowMove = false;
                }

                moveTimer += GetFrameTime();

                if (moveTimer >= moveInterval) {
                    moveTimer = 0;
                    allowMove = true;

                    snake.move();
                    Vector2 head = snake.getHead();
                    if (head.x == food.x && head.y == food.y) {
                        snake.grow();
                        if (!muted_sfx) PlaySound(sfx_food);
                        // apply multiplier for special player name "kamolia"
                        std::string pname = snake.getName();
                        std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
                        int mult = (pname == "kamolia") ? 5 : 1;
                        snake.addScore(scorePerFood * mult);
                        spawnFood();
                    }

                    if (snake.getScore() >= scoreToNext)
                        levelComplete = true;

                    if (checkWallCollision() || checkObstacleCollision() || checkSelfCollision()) {
                        if (!muted_sfx)
                            PlaySound(sfx_collision);

                        collisionFreeze = true;
                        collisionTimer = 0.0;
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
                if (collisionTimer >= 2.0) gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(bgColor);

        int titleW = MeasureText("Snake", 40);
        DrawText("Snake", WINDOW_WIDTH/2 - titleW/2, 20, 40, WHITE);
        DrawText(TextFormat("Score: %d", snake.getScore()), 20, 20, 20, WHITE);
        DrawText(TextFormat("Level: %d  |  Next: %d", level, scoreToNext), 20, 45, 18, GRAY);
        DrawText("P = pause", WINDOW_WIDTH - 120, 20, 18, GRAY);

        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE",
            mute_btn.x + (mute_btn.width - muteW)/2,
            mute_btn.y + (mute_btn.height - 20)/2, 20,
            mutedBGm ? GREEN : RED);

        DrawRectangleRec(sfx_btn, DARKBLUE);
        const char* sfxLabel = muted_sfx ? "SFX ON" : "SFX OFF";
        int sfxW = MeasureText(sfxLabel, 20);
        DrawText(sfxLabel,
            sfx_btn.x + (sfx_btn.width - sfxW)/2,
            sfx_btn.y + (sfx_btn.height - 20)/2, 20,
            muted_sfx ? GREEN : RED);

        Color cellA = {26, 26, 52, 255};
        Color cellB = {18, 18, 38, 255};

        for (int gy = 0; gy < GRID_HEIGHT; gy++) {
            for (int gx = 0; gx < GRID_WIDTH; gx++) {
                Color c = ((gx + gy) % 2 == 0) ? cellA : cellB;
                DrawRectangle(gx * CELL_SIZE + OFFSET_X, gy * CELL_SIZE + OFFSET_Y, CELL_SIZE, CELL_SIZE, c);
            }
        }
        snake.draw(collisionFreeze, snake.getHead());
        float fcx = food.x * CELL_SIZE + OFFSET_X + CELL_SIZE / 2.0f;
        float fcy = food.y * CELL_SIZE + OFFSET_Y + CELL_SIZE / 2.0f;
        float armLen = CELL_SIZE * 0.35f;
        float thick  = CELL_SIZE * 0.15f;
        DrawRectangle(fcx - armLen, fcy - thick/2, armLen*2, thick, DARKGREEN);
        DrawRectangle(fcx - thick/2, fcy - armLen, thick, armLen*2, DARKGREEN);

        for (auto &obs : obstacles) {
            DrawRectangle(obs.x * CELL_SIZE + OFFSET_X,
                obs.y * CELL_SIZE + OFFSET_Y,
                CELL_SIZE, CELL_SIZE, obsColor);
            DrawRectangleLines(obs.x * CELL_SIZE + OFFSET_X,
                obs.y * CELL_SIZE + OFFSET_Y,
                CELL_SIZE, CELL_SIZE, WHITE);
        }

        if (collisionFreeze) {
            Vector2 head = snake.getHead();

            int px = head.x * CELL_SIZE + OFFSET_X;
            int py = head.y * CELL_SIZE + OFFSET_Y;

            DrawRectangle(px, py, CELL_SIZE, CELL_SIZE, {255, 0, 0, 150});
            DrawRectangleLines(px, py, CELL_SIZE, CELL_SIZE, RED);
            DrawLine(px, py, px + CELL_SIZE, py + CELL_SIZE, RED);
            DrawLine(px + CELL_SIZE, py, px, py + CELL_SIZE, RED);

            int msgW = MeasureText("SELF COLLISION!", 20);
            DrawText(
                "SELF COLLISION!",
                WINDOW_WIDTH/2 - msgW/2,
                OFFSET_Y - 30,
                20,
                RED
            );
        }
        if (paused && !collisionFreeze) {
            int pw = MeasureText("PAUSED", 30);
            DrawText("PAUSED", WINDOW_WIDTH/2 - pw/2, WINDOW_HEIGHT/2, 30, WHITE);
        }

        EndDrawing();
    }

    // If window was closed during gameplay, exit immediately
    if (WindowShouldClose()) return 0;

    // end screen
    updateLeaderboard(leaderboard_levels, snake.getName(), snake.getScore());
    int choice = showPostGame_menu(false, levelComplete, level, leaderboard_levels);
    if (levelComplete && level < 3 && choice == 1) return 1;
    return choice == 1 ? -1 : 0;
}