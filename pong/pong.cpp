#include "pong.h"
#include"pong/ball.h"
Pong::Pong(const Player &p1,const Player &p2, const Ball &ball, const int threshold) : p1(p1), p2(p2), ball(ball) {
    setThreshold(threshold);
    ai.setName("AI");
    gamesP1 = 0;
    gamesP2 = 0;
    this->ball.setPosition(0.0, 0.0);
    this->ball.setSpeed(0, 0);
    this->ball.setRadius(0);
    paddle1Rect = {10,300,25,120};
    paddle2Rect = {1245,300,25,120};
    aiRect = {1245,300,25,120};
    // resetRound();
}
void Pong::moveAi() {
    float paddleSpeed=7.0f;
   if (ball.getY() < aiRect.y+aiRect.height/2) {
       aiRect.y-=paddleSpeed;
   }  if (ball.getY() >= aiRect.y+aiRect.height/2) {
       aiRect.y+=paddleSpeed;
    }
    if (aiRect.y < 0) aiRect.y = 0;
    if (aiRect.y+aiRect.height >= GetScreenHeight()) aiRect.y = GetScreenHeight()-aiRect.height;
}
void Pong::movePaddel1() {
        float paddleSpeed=7.0f;
    if (IsKeyDown(KEY_UP)) {
        paddle1Rect.y-=paddleSpeed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        paddle1Rect.y+=paddleSpeed;
    }
    if (paddle1Rect.y < 0) paddle1Rect.y = 0;
    if (paddle1Rect.y+paddle1Rect.height >= GetScreenHeight()) paddle1Rect.y = GetScreenHeight()-paddle1Rect.height;
}
void  Pong::movePaddel2() {
    float paddleSpeed=7.0f;
    if (IsKeyDown(KEY_W)) {
        paddle2Rect.y-=paddleSpeed;
    }
    if (IsKeyDown(KEY_S)) {
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
    InitWindow(1280, 720, "pong");
    SetTargetFPS(60);
    ball.setPosition(640,360);
    ball.setSpeed(10,10);
    ball.setRadius(20);
    bool paused = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (!paused) {
            ball.update();
            movePaddel1();
            movePaddel2();
        }
        //p2 scores
        if (ball.getX() - ball.getRadius() <= 0)
        {
            p2.incrementScore();
            ball.setPosition(640, 360);
            ball.setSpeed(7, 7);
        }
        //p1 scores
        if (ball.getX() + ball.getRadius() >= GetScreenWidth()) {
            p1.incrementScore();
            ball.setPosition(640, 360);
            ball.setSpeed(-7, 7);
        }
        if (p1.getScore() >= threshold || p2.getScore() >= threshold) {
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
        //drawing
        DrawLine(640,0,640,720,WHITE);
        ball.draw();
        DrawRectangleRec(paddle1Rect, c1);
        DrawRectangleRec(paddle2Rect, c2);
        DrawText(TextFormat("%d", p1.getScore()), 600, 20, 40, WHITE);
        DrawText(TextFormat("%d", p2.getScore()), 680, 20, 40, WHITE);
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
    InitWindow(1280, 720, "pong");
    SetTargetFPS(60);
ball.setPosition(640,360);
    ball.setSpeed(10,10);
    ball.setRadius(20);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (!paused) {
            ball.update();
        movePaddel1();
        moveAi();
        }
        // AI scores
        if (ball.getX() - ball.getRadius() <= 0)
        {
            ai.incrementScore();

            ball.setPosition(640, 360);
            ball.setSpeed(7, 7);
        }

        // Player scores
        if (ball.getX() + ball.getRadius() >= GetScreenWidth())
        {
            p1.incrementScore();

            ball.setPosition(640, 360);
            ball.setSpeed(-7, 7);
        }
        if (p1.getScore() >= threshold || ai.getScore() >= threshold)
        {
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