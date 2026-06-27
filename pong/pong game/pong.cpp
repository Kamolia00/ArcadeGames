#include "pong/pong game/pong.h"
#include"pong/pong game/ball.h"
#include <cmath>
extern bool mutedBGm;
extern Music bgm;
extern Rectangle mute_btn;
extern  int STAR_COUNT;
extern float starX[], starY[], starSpeed[], starSize[];
extern float rocketX, rocketY, rocketSpeed;

namespace {
constexpr float kCenterX = 640.0f;
constexpr float kCenterY = 360.0f;
constexpr int kServeSpeedX = 12;
constexpr int kServeSpeedY = 12;
constexpr double kRoundCountdownSeconds = 3.0;

int GetCountdownSecondsLeft(double countdownEnd) {
    double remaining = countdownEnd - GetTime();
    if (remaining <= 0.0) {
        return 0;
    }
    return static_cast<int>(std::ceil(remaining));
}

void StartRoundCountdown(Ball &ball, bool &countdownActive, double &countdownEnd) {
    ball.setPosition(kCenterX, kCenterY);
    ball.setSpeed(0, 0);
    countdownActive = true;
    countdownEnd = GetTime() + kRoundCountdownSeconds;
}
}

Pong::Pong( Player &p1, Player &p2, const Ball &ball, int threshold) : p1(p1), p2(p2), ball(ball) {
    setThreshold(threshold);
    ai.setName("AI");
    gamesP1 = 0;
    gamesP2 = 0;
    aiWins=0;
    this->ball.setPosition(0.0, 0.0);
    this->ball.setSpeed(0, 0);
    this->ball.setRadius(0);
    paddle1Rect = {10,300,25,120};
    paddle2Rect = {1245,300,25,120};
    aiRect = {1245,300,25,120};
    // resetRound();
}

int Pong::getAiWins() const {

    return aiWins;
}
int Pong::getGamesP1() const {
    return gamesP1;
}
int Pong::getGamesP2() const {
    return gamesP2;
}
void Pong::moveAi() {
    float paddleSpeed=8.0f;
   if (ball.getY() < aiRect.y+aiRect.height/2) {
       aiRect.y-=paddleSpeed;
   }  if (ball.getY() >= aiRect.y+aiRect.height/2) {
       aiRect.y+=paddleSpeed;
    }
    if (aiRect.y < 0) aiRect.y = 0;
    if (aiRect.y+aiRect.height >= GetScreenHeight()) aiRect.y = GetScreenHeight()-aiRect.height;
}
void Pong::movePaddel1() {
        float paddleSpeed=8.0f;
    if (IsKeyDown(KEY_W)) {
        paddle1Rect.y-=paddleSpeed;
    }
    if (IsKeyDown(KEY_S)) {
        paddle1Rect.y+=paddleSpeed;
    }
    if (paddle1Rect.y < 0) paddle1Rect.y = 0;
    if (paddle1Rect.y+paddle1Rect.height >= GetScreenHeight()) paddle1Rect.y = GetScreenHeight()-paddle1Rect.height;
}
void  Pong::movePaddel2() {
    float paddleSpeed=8.0f;
    if (IsKeyDown(KEY_UP)) {
        paddle2Rect.y-=paddleSpeed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        paddle2Rect.y+=paddleSpeed;
}
    if (paddle2Rect.y < 0) paddle2Rect.y = 0;
    if (paddle2Rect.y+paddle2Rect.height >= GetScreenHeight()) paddle2Rect.y = GetScreenHeight()-paddle2Rect.height;
}
void Pong::playGame_pvp() {
    Color c1,c2;
    switch(p1.getSymbol()) {
        case 'r': c1 = RED; break;
        case 'g': c1 = GREEN; break;
        case 'b': c1 = BLUE; break;
        default:  c1 = WHITE;
    }
    switch(p2.getSymbol()) {
        case 'r': c2 = RED; break;
        case 'g': c2 = GREEN; break;
        case 'b': c2 = BLUE; break;
        default:  c2 = WHITE;
    }
    p1.setScore(0);
    p2.setScore(0);
    paddle1Rect = {10,300,25,120};
    paddle2Rect = {1245,300,25,120};
    ball.setPosition(kCenterX,kCenterY);
    ball.setSpeed(0,0);
    ball.setRadius(20);
    bool countdownActive = false;
    double countdownEnd = 0.0;
    int serveSpeedX = kServeSpeedX;
    bool paused = false;
    StartRoundCountdown(ball, countdownActive, countdownEnd);
    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm  = !mutedBGm;
        }
        if (countdownActive && GetCountdownSecondsLeft(countdownEnd) == 0) {
            countdownActive = false;
            ball.setSpeed(serveSpeedX, kServeSpeedY);
        }
        BeginDrawing();
        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (!paused && !countdownActive) {
            ball.update();
        }
        if (!paused) {
            movePaddel1();
            movePaddel2();
        }
        //p2 scores
        if (!countdownActive && ball.getX() - ball.getRadius() <= 0)
        {
            p2.incrementScore();
            serveSpeedX = -kServeSpeedX;
            StartRoundCountdown(ball, countdownActive, countdownEnd);
        }
        //p1 scores
        if (!countdownActive && ball.getX() + ball.getRadius() >= GetScreenWidth()) {
            p1.incrementScore();
            serveSpeedX = kServeSpeedX;
            StartRoundCountdown(ball, countdownActive, countdownEnd);
        }
        if (p1.getScore() >= threshold ) {
            gamesP1++;
            break;
        }
        if (p2.getScore() >= threshold) {
            gamesP2++;
            break;
        }
        // check for collisions
        if (CheckCollisionCircleRec(Vector2{ball.getX(), ball.getY()},ball.getRadius(),Rectangle{paddle1Rect.x,paddle1Rect.y,paddle1Rect.width,paddle1Rect.height})){
            ball.setSpeed(-ball.getSpeedX(),ball.getSpeedY());
        }
        if (CheckCollisionCircleRec(Vector2{ball.getX(), ball.getY()},ball.getRadius(),Rectangle{paddle2Rect.x,paddle2Rect.y,paddle2Rect.width,paddle2Rect.height})) {
            ball.setSpeed(-ball.getSpeedX(),ball.getSpeedY());
        }
        ClearBackground({20, 20, 40, 255});
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE",
            mute_btn.x + (mute_btn.width - muteW)/2,
            mute_btn.y + (mute_btn.height - 20)/2, 20,
            mutedBGm ? GREEN : RED);

        //drawing
        DrawLine(640,0,640,720,WHITE);
        ball.draw();
        DrawRectangleRec(paddle1Rect, c1);
        DrawRectangleRec(paddle2Rect, c2);
        DrawText(TextFormat("%d", p1.getScore()), 600, 20, 40, WHITE);
        DrawText(TextFormat("%d", p2.getScore()), 680, 20, 40, WHITE);
        if (countdownActive) {
            int countdown = GetCountdownSecondsLeft(countdownEnd);
            if (countdown > 0) {
                const char *countdownText = TextFormat("%d", countdown);
                int countdownSize = 90;
                DrawText(
                    countdownText,
                    GetScreenWidth()/2 - MeasureText(countdownText, countdownSize)/2,
                    GetScreenHeight()/2 - countdownSize/2,
                    countdownSize,
                    WHITE
                );
            }
        }
        if (paused)
        {
            DrawText(
                "PAUSED",
                GetScreenWidth()/2 - MeasureText("PAUSED", 50)/2,
                GetScreenHeight()/2 - 25,
                 50,
                WHITE);

            DrawText(
    "Press P to resume",
    GetScreenWidth()/2 - MeasureText("Press P to resume", 30)/2,
    GetScreenHeight()/2 + 40,
    30,
    GRAY
);

        }
        if (!paused)
        {
            const char* pauseText = "Press P to Pause";

            DrawText(
                pauseText,
                GetScreenWidth() - MeasureText(pauseText, 20) - 20,
                20,
                20,
                GRAY
            );
        }
        EndDrawing();
    }
while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground({20, 20, 40, 255});
    std::string winner =
        (p1.getScore() >= threshold)
        ? p1.getName() + " Wins!"
        : p2.getName() + " Wins!";
    int fontSize1 = 60;
    int fontSize2 = 30;
    int textWidth1 = MeasureText(winner.c_str(), fontSize1);
    int textWidth2 = MeasureText("Press ENTER to continue", fontSize2);
    DrawText(            winner.c_str(),
            GetScreenWidth()/2 - textWidth1/2,
            GetScreenHeight()/2 - 50,
            fontSize1,
            GREEN);
    DrawText(
        "Press ENTER to continue",
        GetScreenWidth()/2 - textWidth2/2,
        GetScreenHeight()/2 + 30,
        fontSize2,
        WHITE
    );

    EndDrawing();

    if (IsKeyPressed(KEY_ENTER))
        break;
}}
void Pong::setThreshold(int n) {
    threshold = n;
}
void Pong::playGame_ai() {
    Color c;
    switch(p1.getSymbol()) {
        case 'r': c = RED; break;
        case 'g': c = GREEN; break;
        case 'b': c = BLUE; break;
        default:  c = WHITE;
    }

    bool paused = false;
    p1.setScore(0);
    ai.setScore(0);
    paddle1Rect = {10,300,25,120};
    aiRect = {1245,300,25,120};
ball.setPosition(kCenterX,kCenterY);
    ball.setSpeed(0,0);
    ball.setRadius(20);
    bool countdownActive = false;
    double countdownEnd = 0.0;
    int serveSpeedX = kServeSpeedX;
    StartRoundCountdown(ball, countdownActive, countdownEnd);

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        if (mutedBGm) PauseMusicStream(bgm);
        else ResumeMusicStream(bgm);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            if (CheckCollisionPointRec(m, mute_btn)) mutedBGm  = !mutedBGm;
        }

        if (countdownActive && GetCountdownSecondsLeft(countdownEnd) == 0) {
            countdownActive = false;
            ball.setSpeed(serveSpeedX, kServeSpeedY);
        }

        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (!paused && !countdownActive) {
            ball.update();
        }
        if (!paused) {
        movePaddel1();
        moveAi();
        }
        // AI scores
        if (!countdownActive && ball.getX() - ball.getRadius() <= 0)
        {
            ai.incrementScore();
            serveSpeedX = -kServeSpeedX;
            StartRoundCountdown(ball, countdownActive, countdownEnd);
        }

        // Player scores
        if (!countdownActive && ball.getX() + ball.getRadius() >= GetScreenWidth())
        {
            p1.incrementScore();
            serveSpeedX = kServeSpeedX;
            StartRoundCountdown(ball, countdownActive, countdownEnd);
        }
        if (p1.getScore() >= threshold )
        {
            gamesP1++;
            break;
        }
        if (ai.getScore() >= threshold) {
            gamesP2++;
            break;
        }
        // check for collisions
        if (CheckCollisionCircleRec(Vector2{ball.getX(), ball.getY()},ball.getRadius(),Rectangle{paddle1Rect.x,paddle1Rect.y,paddle1Rect.width,paddle1Rect.height})){
        ball.setSpeed(-ball.getSpeedX(),ball.getSpeedY());
        }
        if (CheckCollisionCircleRec(Vector2{ball.getX(), ball.getY()},ball.getRadius(),Rectangle{aiRect.x,aiRect.y,aiRect.width,aiRect.height})) {
            ball.setSpeed(-ball.getSpeedX(),ball.getSpeedY());
        }
        ClearBackground({20, 20, 40, 255});
        //drawing
        DrawRectangleRec(mute_btn, DARKBLUE);
        int muteW = MeasureText(mutedBGm ? "SOUND" : "MUTE", 20);
        DrawText(mutedBGm ? "SOUND" : "MUTE",
            mute_btn.x + (mute_btn.width - muteW)/2,
            mute_btn.y + (mute_btn.height - 20)/2, 20,
            mutedBGm ? GREEN : RED);

        DrawLine(640,0,640,720,WHITE);
        ball.draw();
    Color c2,r=RED;
        if (c.r == r.r &&
    c.g == r.g &&
    c.b == r.b &&
    c.a == r.a)
        {
            c2 = WHITE;
        }
        else
        {
            c2 = RED;
        }
        DrawRectangleRec(paddle1Rect, c);
        DrawRectangleRec(aiRect, c2);
        DrawText(TextFormat("%d", p1.getScore()), 600, 20, 40, WHITE);
        DrawText(TextFormat("%d", ai.getScore()), 680, 20, 40, RED);
        if (countdownActive) {
            int countdown = GetCountdownSecondsLeft(countdownEnd);
            if (countdown > 0) {
                const char *countdownText = TextFormat("%d", countdown);
                int countdownSize = 90;
                DrawText(
                    countdownText,
                    GetScreenWidth()/2 - MeasureText(countdownText, countdownSize)/2,
                    GetScreenHeight()/2 - countdownSize/2,
                    countdownSize,
                    WHITE
                );
            }
        }
        if (paused)
        {
            DrawText(
                "PAUSED",
                GetScreenWidth()/2 - MeasureText("PAUSED", 50)/2,
                GetScreenHeight()/2 - 25,
                50,
                WHITE
            );

            DrawText(
                "Press P to resume",
                GetScreenWidth()/2 - MeasureText("Press P to resume", 30)/2,
                GetScreenHeight()/2 + 40,
                30,
                GRAY
            );
        }
        if (!paused)
        {
            const char* pauseText = "Press P to Pause";

            DrawText(
                pauseText,
                GetScreenWidth() - MeasureText(pauseText, 20) - 20,
                20,
                20,
                GRAY
            );
        }
        EndDrawing();
}
    while (!WindowShouldClose())
    {
        bool ai_w=false;
        BeginDrawing();
        ClearBackground({20, 20, 40, 255});

        std::string winner =
            (p1.getScore() >= threshold)
            ? p1.getName() + " Wins!"
            : ai.getName() + " Wins!";

        int fontSize1 = 60;
        int fontSize2 = 30;

        int textWidth1 = MeasureText(winner.c_str(), fontSize1);
        int textWidth2 = MeasureText("Press ENTER to continue", fontSize2);
if (winner == ai.getName() + " Wins!")
    ai_w=true;
        DrawText(
            winner.c_str(),
            GetScreenWidth()/2 - textWidth1/2,
            GetScreenHeight()/2 - 50,
            fontSize1,
            ai_w?RED:GREEN
        );

        DrawText(
            "Press ENTER to continue",
            GetScreenWidth()/2 - textWidth2/2,
            GetScreenHeight()/2 + 30,
            fontSize2,
            WHITE
        );

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            break;
    }}